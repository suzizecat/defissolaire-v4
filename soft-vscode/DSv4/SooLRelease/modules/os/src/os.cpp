/**
 * Copyright (c) 2018 FAUCHER Julien & FRANCE Loic
 * This file is part of SooL OS module.
 *
 *  SooL OS module is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  SooL OS module is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SooL OS module. If not, see <https://www.gnu.org/licenses/>.
 */
#include "../include/os.h"
#include "../include/events.h"
#include "../include/task.h"

// ARM Cortex-M7 instruction set :
// http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0646b/CIHJJEIF.html

namespace sool
{
	namespace os
	{

//######################################################################################################################
//#                                             private members definition                                             #
//######################################################################################################################

		OS::TaskCtrl *OS::_running_task = nullptr;
		OS::TaskCtrl *OS::_ready_tasks_list = nullptr;
		OS::TaskCtrl *OS::_delayed_tasks_list = nullptr;
		EventGroup *OS::_event_groups_list = nullptr;
		uint32_t OS::_critical_section_counter = 0;

//######################################################################################################################
//#                                                task lists movements                                                #
//######################################################################################################################

		void OS::_task_remove(OS::TaskCtrl *task)
		{
			//If the task is at the beginning of the list, the list must now point to the next task.
			//Otherwise, the previous task must now point to the next one.
			//If the task is not in any list, it is not yet handled by the OS
			//If the task is the one running, the pointer to the running task in the OS must stay on this task
			//until the actual change happens.
			if(task->list == &_running_task) {
				return;
			}

			if (task->prev_task != nullptr) {
				task->prev_task->next_task = task->next_task;
			}

			else if (task->list != nullptr && task->list != &_running_task)
				*(task->list) = task->next_task;

			if (task->next_task != nullptr) {
				//if the task was not running or ready to be run, it has a timeout.
				//Due to the way timeout works in the OS, we must transfer the timeout to the next task
				if (task->state >= TaskState::DELAYED) {
					if (task->next_task->timeout != Task::INFINITE_DELAY)
						task->next_task->timeout += task->timeout;
				}
				task->next_task->prev_task = task->prev_task;
			}
		}

		void OS::_set_task_ready(OS::TaskCtrl *task)
		{
			enter_critical();
			if (task->list != nullptr)
			{
				if (task->state == TaskState::READY)
					return; // task already ready to run
				_task_remove(task);
			}
			TaskCtrl *prev = nullptr;
			TaskCtrl *next = _ready_tasks_list;
			while (next != nullptr && next->priority <= task->priority)
			{
				prev = next;
				next = next->next_task;
			}

			if (prev == nullptr)
				_ready_tasks_list = task;
			else
				prev->next_task = task;

			task->prev_task = prev;
			task->next_task = next;
			if(next != nullptr)
				next->prev_task = task;

			task->list = &_ready_tasks_list;
			task->state = TaskState::READY;

			exit_critical();
		}

		void OS::_task_wait(OS::TaskCtrl *task, uint32_t ticks_to_wait)
		{
			if (task == nullptr) task = _running_task;

			if (ticks_to_wait == 0)
			{
				if (_ready_tasks_list->priority <= task->priority)
					_set_task_ready(task);
				else
					return;
			}
			else
			{
				enter_critical();

				_task_remove(task);

				//Place the task in the delayed tasks list, always sorted by timeout.
				//The attribute "timeout" in the task is in fact the time to wait
				//once the previous task in the list is done waiting.
				//Except for infinite timeout: All tasks with infinite timeout are placed
				//at the end with no consideration for priority, with the same value
				//for the timeout attribute (Task::INFINITE_DELAY = ~0 = 0xFFFFFFFF = 2^32 - 1)

				TaskCtrl *prev = nullptr;
				TaskCtrl *next = _delayed_tasks_list;

				task->list = &_delayed_tasks_list;
				task->prev_task = nullptr;
				task->state = TaskState::DELAYED;

				if (ticks_to_wait == Task::INFINITE_DELAY)
				{
					while (next != nullptr && next->timeout != Task::INFINITE_DELAY)
					{
						prev = next;
						next = next->next_task;
					}
					task->timeout = Task::INFINITE_DELAY;
				}
				else
				{
					while (next != nullptr && (
							(next->timeout < ticks_to_wait) ||
							(next->timeout == ticks_to_wait && next->priority <= task->priority)
					)) {
						ticks_to_wait -= next->timeout;
						prev = next;
						next = next->next_task;
					}
					task->timeout = ticks_to_wait;
					if (next != nullptr)
						next->timeout -= ticks_to_wait;
				}
				if (prev == nullptr)
					_delayed_tasks_list = task;
				else
					prev->next_task = task;
				task->prev_task = prev;
				task->next_task = next;

				if (next != nullptr)
					next->prev_task = task;

				exit_critical();
			}
			asm("nop");
		}

//#####################################################################################################################
//#                                                 OS initialization                                                 #
//#####################################################################################################################

		static void enable_VFP()
		{
#if defined(CORTEX_M7) || defined(CORTEX_M4)
			__asm volatile
			(
				"ldr.w r0, =0xE000ED88		\n" /* The FPU enable bits are in the CPACR. */
				"ldr r1, [r0]				\n"
				"orr r1, r1, #( 0xf << 20 )	\n" /* Enable CP10 and CP11 coprocessors, then save back. */
				"str r1, [r0]				\n"
			);
#endif
		}

		void OS::_idle_task_function(void *parameters)
		{
			for (;;) {
				__asm volatile(
					"dsb \n"
					"wfi \n"
					"isb \n"
				);
			}
		}

		static inline __attribute__(( always_inline)) void start_first_task( void )
		{
			__asm volatile(
				" mov r0, #0			\n"
				" msr control, r0		\n" // clears the bit indicating the FPU is in use
				" cpsie i				\n" // Globally enable interrupts.
				" cpsie f				\n"
				" dsb					\n"
				" isb					\n"
				" svc 0					\n" // System call to start first task.
				" nop					\n"
				::: "r0"
			);
		}

		static inline __attribute__(( always_inline)) void raise_BASEPRI( void )
		{
		uint32_t new_BASEPRI;

			__asm volatile
			(
				"mov %0, %1			\n"
				"cpsid i			\n"
				"msr basepri, %0	\n"
				"isb				\n"
				"dsb				\n"
				"cpsie i			\n"
				:"=r" (new_BASEPRI) : "i" ( 4 << (8 - 4) ) : "memory"
			);
		}

		void OS::start()
		{
			static uint32_t idle_stack[32] = {0};
			static Task idle_task = StaticTask(OS::_idle_task_function, ~0, idle_stack, 32, nullptr); // lowest priority, 150 bytes of stack, no parameter
			idle_task.wake_up();

			_running_task = _ready_tasks_list;
			_ready_tasks_list = _ready_tasks_list->next_task;

			_running_task->state = TaskState::RUNNING;
			_running_task->next_task = nullptr;
			_running_task->list = &_running_task;

			if(_ready_tasks_list != nullptr)
				_ready_tasks_list->prev_task = nullptr;

			__asm volatile(
					"cpsid i" //disable all interrupts. interrupt re-enabling in start_first_task()
			);
			raise_BASEPRI();
#if defined(STM32F0     ) || defined(STM32L0     ) || defined(STM32L1     )
			//NVIC_SetPriority(SVC_IRQn, 0x0f); /* Lowest possible priority */
#else
			//NVIC_SetPriority(SVCall_IRQn, 0x0f); /* Lowest possible priority */
#endif
			NVIC_SetPriority(PendSV_IRQn, 0x0f); /* Lowest possible priority */
			//NVIC_EnableIRQ(SVCall_IRQn);
			//NVIC_EnableIRQ(PendSV_IRQn);
			if((SysTick->CTRL & SysTick_CTRL_ENABLE_Msk) == SysTick_CTRL_ENABLE_Msk) //if SysTick is already configured (i.e. enabled) yet
			{
				if((SysTick->CTRL & SysTick_CTRL_TICKINT_Msk) != SysTick_CTRL_TICKINT_Msk) //SysTick was configured but interrupts not enabled
					SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
			}
			else
			{
				SysTick_Config(SystemCoreClock / 1000); // set Systick to 1 ms delay, clock source being System core clock and interrupts enable
			}

			NVIC_SetPriority(SysTick_IRQn, 0x00); /* Highest possible priority */

			enable_VFP();
			*((volatile uint32_t*)0xe000ef34) |= 0x3ul << 30ul; // Lazy save always.

			start_first_task();

			while(1);
		}

		void OS::init()
		{
			OS::_running_task = nullptr;
			OS::_event_groups_list = nullptr;
			OS::_ready_tasks_list = nullptr;
			OS::_delayed_tasks_list = nullptr;
			OS::_critical_section_counter = 0;
		}

//#####################################################################################################################
//#                                                  critical section                                                 #
//#####################################################################################################################

		void OS::exit_critical()
		{
			if(_critical_section_counter > 0) {
				--_critical_section_counter;
				_switch_task_if_needed();
			}
		}
		void OS::_switch_task_if_needed()
		{
			if((_ready_tasks_list == nullptr) || (_critical_section_counter > 0) || (_running_task == nullptr))
				return;
			else if(_running_task->state != TaskState::RUNNING)
				OS::_request_task_switch();
			else if(_running_task->priority > _ready_tasks_list->priority)
			{
				OS::_set_task_ready(_running_task);
				//OS::request_task_switch();
			}
		}

//######################################################################################################################
//#                                                  context switching                                                 #
//######################################################################################################################

		void OS::SysTick_handler()
		{
			__asm volatile("cpsid i"); //disable all interrupts
			TaskCtrl *task = _delayed_tasks_list;
			if (task != nullptr && task->timeout != Task::INFINITE_DELAY) {
				task->timeout--;
				while (task != nullptr && task->timeout == 0) {
					_delayed_tasks_list = task->next_task;	// move list pointer from 1st element to 2nd element.
					_set_task_ready(task);                   // move task from _delayed_tasks_list to _ready_tasks_list
					task = _delayed_tasks_list;             // change local variable to new first element of list
				}
				if (task != nullptr) {
					task->prev_task = nullptr;
				}
			}

			EventGroup *evt_grp = _event_groups_list;
			while (evt_grp != nullptr) {
				evt_grp->tick();
				evt_grp = evt_grp->_next_event_group;
			}
			//_switch_task_if_needed();
			/*
			if (need_task_switch()) //a higher priority task is waiting for the processor
			{
				OS::task_wait(OS::_running_task, 0);
			}
			*/

			__asm volatile("cpsie i");
		}

		void OS::_request_task_switch()
		{
			if(!OS::is_section_critical())
			{
				SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
				__asm volatile("dsb" ::: "memory");
				__asm volatile("isb");
			}
		}
	}
}

void SVC_Handler(void)
{
#if defined(CORTEX_M4) || defined(CORTEX_M7)
	__asm volatile (
		"ldr r1, %[first_task]		\n" // get the  address of the first task control. r1 = OS::_running_task
		"ldr r0, [r1]				\n" // The first item in the task control is the task top of stack.
		"ldmia r0!, {r4-r11, r14}	\n" // Pop the registers that are not automatically saved on exception entry and the critical nesting count.
		"msr psp, r0				\n" // Restore the task stack pointer.
		"isb						\n"
		"mov r0, #0 				\n"
		"msr	basepri, r0			\n"
		"bx r14						\n"
		"							\n"
		".align 2					\n"
		::[first_task] "m" (sool::os::OS::_running_task):
	);
#endif
}

void __sool_os_switch_task(void)
{
	__asm volatile(
		"ldr r2, %[curr_task]		\n" // load r2 with the value of curr_task, address of currently running task handler
		"str r0, [r2]				\n" // Save the new top of stack into the task handler's first attribute (top_of_stack)
		::[curr_task] "m" (sool::os::OS::_running_task) //link [curr_task] in asm code to the running task control address, located in the memory.
		 : "r0", "r2", "memory"
	);
	sool::os::OS::_running_task = sool::os::OS::_ready_tasks_list;
	sool::os::OS::_ready_tasks_list = sool::os::OS::_ready_tasks_list->next_task;

	sool::os::OS::_running_task->state = sool::os::TaskState::RUNNING;
	sool::os::OS::_running_task->next_task = nullptr;
	sool::os::OS::_running_task->list = &sool::os::OS::_running_task;

	if(sool::os::OS::_ready_tasks_list != nullptr)
		sool::os::OS::_ready_tasks_list->prev_task = nullptr;

	__asm volatile(
		"ldr r1, %[next_task]		\n"
		"ldr r0, [r1]				\n"
		::[next_task] "m" (sool::os::OS::_running_task) //link [next_task] in asm code to the next task control address, located in the memory.
		 : "r0", "r1", "memory"
	);
}

__attribute__((naked)) void PendSV_Handler(void)
{
#if defined(CORTEX_M7) || defined(CORTEX_M4)
	__asm volatile(
		"cpsid i					\n" // disable all interrupts
//- - - - - - - - - - - - - - - - - - - - - - - -STORE REGISTERS IN MEMORY - - - - - - - - - - - - - - - - - - - - - - -
		"mrs r0, PSP				\n" // move Process Stack Pointer (PSP) into r0
		"isb						\n" // flush processor pipeline

		"tst r14, #0x10				\n" // if the task is using FPU Context, ...
		"it eq						\n"
		"vstmdbeq r0!, {s16-s31}	\n"	// ... push extension registers (s16 to s31)
		"stmdb r0!, {r4-r11, r14}	\n" // Push core registers onto the process stack.
										// r0 contains the addr of the top of the stack.
//- - - - - - - - - - - - - - - - - - - - - - - - - - -TASK SWITCH - - - - - - - - - - - - - - - - - - - - - - - - - - -
		"bl __sool_os_switch_task	\n"
//- - - - - - - - - - - - - - - - - - - - - - - LOAD REGISTERS FROM MEMORY - - - - - - - - - - - - - - - - - - - - - - -
		"ldmia r0!, {r4-r11, r14}	\n" // Pop core registers from the process stack.

		"tst r14, #0x10				\n" // If the task is using FPU context,
		"it eq						\n"
		"vldmiaeq r0!, {s16-s31}	\n" // pop the extension registers too

		"msr PSP, r0				\n" // set the psp
		"isb						\n"
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - END- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		"cpsie i					\n" // re-enable all interrupts
		"bx lr						\n"
		".align 2					\n"
	);
#endif
}
