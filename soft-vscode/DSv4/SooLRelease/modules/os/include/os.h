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
#ifndef SOOL_OS_H
#define SOOL_OS_H

#include "../../../core/system/include/system_stm32.h"

#include <cstdint>


extern "C" {
void SVC_Handler(void);
//void SysTick_Handler(void);
void PendSV_Handler(void);
void __sool_os_switch_task(void);
}

namespace sool
{
	namespace os
	{
		class Task;

		class EventGroup;

//######################################################################################################################
//#                                                 enums declaration                                                  #
//######################################################################################################################

		enum class TaskState : uint8_t
		{
			RUNNING = 0,
			READY = 1,
			PAUSED = 2,
			DELAYED = 3,
			WAITING_EVENT = 4,
			DELETED = 5
		};

//######################################################################################################################
//#                                                 class declaration                                                  #
//######################################################################################################################
		class OS
		{
//______________________________________________________________________________________________________________________
//--------------------------------------------------- TaskAttributes --------------------------------------------------

//______________________________________________________________________________________________________________________
//------------------------------------------------------ TaskCtrl ------------------------------------------------------
			struct TaskCtrl
			{
//- - - - - - - - - - - - - - - - - - - - - - - - - -stack attributes- - - - - - - - - - - - - - - - - - - - - - - - - -
				/**
				 * MUST BE THE FIRST ITEM OF THE STRUCT.
				 * Location of the last item placed on the stack.
				 * Used in the PendSV interrupt to switch the context when changing running task.
				 */
				volatile uint32_t *top_of_stack;
				/**
				 * Start of the task stack.
				 */
				volatile void *stack_start;
//- - - - - - - - - - - - - - - - - - - - - - - - linked list attributes - - - - - - - - - - - - - - - - - - - - - - - -
				/**
				 * Link to the previous task in the linked list, or 0 if the task is running,
				 * or the address of the list if it is tht first element of the list
				 * (address of the list : address of the pointer to the element).
				 */
				TaskCtrl *prev_task;
				/**
				 * Link to the next task in the linked list, or 0.
				 */
				TaskCtrl *next_task;
				/**
				 * Pointer to the list (pointer to pointer to the first element)
				 */
				TaskCtrl **list;
//- - - - - - - - - - - - - - - - - - - - - - informations for waiting lists - - - - - - - - - - - - - - - - - - - - - -
				/**
				 * Priority of the task. Lower is better. (0 : max priority)
				 * Determines its position in the ready tasks list.
				 */
				uint32_t priority;
				/**
				 * Time to wait (in system ticks) when in the delayed tasks list,
				 * or timeout when when in an event group tasks list
				 */
				uint32_t timeout;
				/**
				 * Mask used when in the event-waiting tasks list. When an event occurs in the event group,
				 * the corresponding bit is cleared. When all bits of all event groups are cleared, the task is woken up
				 */
				uint32_t event_mask;

				/**
				 * Current state of the task.
				 */
				struct {
					TaskState state: 8;
					uint32_t evt_clear_on_exit : 1;
					uint32_t evt_wait_all : 1;
					uint32_t : 22;
				};

				TaskCtrl(uint32_t priority, uint32_t *const stack, uint32_t stackSize); //NOLINT
			};
//______________________________________________________________________________________________________________________
//------------------------------------------------- private attributes -------------------------------------------------
//- - - - - - - - - - - - - - - - - - - - - - - - - - - tasks lists- - - - - - - - - - - - - - - - - - - - - - - - - - -
			/**
			 * Pointer to the running tasks.
			 */
			static TaskCtrl *_running_task;
			/**
			 * Linked list containing the tasks ready to run, waiting for the processor. <br/>
			 */
			static TaskCtrl *_ready_tasks_list;
			/**
			 * Linked list containing tasks that are waiting for a certain amount of time
			 * before going back waiting for the processor.
			 */
			static TaskCtrl *_delayed_tasks_list;
			/**
			 * Linked list containing tasks that are waiting for events to happen
			 */
			static EventGroup *_event_groups_list;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - -OS state- - - - - - - - - - - - - - - - - - - - - - - - - - - -
			/**
			 * > 1 if the running task is in a critical section. As called function can require critical sections
			 *  even if they already are in critical sections, this attribute is in fact the level of critical sections in the current code.
			 *  The critical section is considered finished when this number equals 0
			 */
			static uint32_t _critical_section_counter;
//______________________________________________________________________________________________________________________
//--------------------------------------------------- private methods --------------------------------------------------
			/**
			 * Request the PendSV interrupt from the system
			 */
			static void _request_task_switch();

			/**
			 * If the conditions for a task switch are met, the function OS::request_task_switch is called.
			 * The conditions are :
			 * 	- The ready tasks list is not empty
			 * 	- The section is not critical.
			 * 	- Its first element has higher priority than the running task.
			 */
			static void _switch_task_if_needed();

			/**
			 * Called by the OS itself.
			 * Places the task in the ready tasks list, at the position corresponding to its priority.
			 * If the task is currently running, it will yield to ready tasks with greater
			 * or equal priority. If no task fills the condition to replace the running task,
			 * nothing happens.
			 * If the task has higher priority than the running task, a task switch will happen
			 * at the end of this function.
			 * @param task - the task to place in the ready tasks list
			 */
			static void _set_task_ready(TaskCtrl *task);

			/**
			 * Called by the task when it needs to wait a certain amount of time.
			 * Pause the task and place it in the delayed tasks list, at the position
			 * corresponding to the time it needs to wait and to its priority.
			 *
			 * When waiting time has elapsed, the task is placed inside the ready tasks list.
			 *
			 * @param task - the task to pause and place in the delayed tasks list, or nullptr to pause the current task
			 * @param ticks_to_wait - the amount of time (in system ticks) to wait before waking up
			 */
			static void _task_wait(TaskCtrl *task, uint32_t ticks_to_wait);

			/**
			 * Called by the task when it wants to be killed
			 * Remove the task from the OS.
			 * Also used by the OS itself when moving a task from one list to another
			 *
			 * @param task
			 */
			static void _task_remove(TaskCtrl *task);

			static void _idle_task_function(void *parameters);
			static void _switch_task(void);

			friend class Task;

			friend class EventGroup;

			friend void ::PendSV_Handler(void);
			friend void ::SVC_Handler(void);
			friend void ::__sool_os_switch_task(void);
//______________________________________________________________________________________________________________________
//--------------------------------------------------- public methods ---------------------------------------------------
		public:

			/**
			 * Deleted constructor (OS is a static class)
			 */
			OS() = delete;

			/**
			 * Initialize the Operating system. Must be called before adding any task
			 */
			static void init();

			/**
			 * Starts the Operating system.
			 */
			static void start();

			/**
			 * must be called by the software inside the SysTick interrupt handler
			 */
			static void SysTick_handler();

			/**
			 * @return the currently running task, or nullptr if the idle task is running
			 */
			static Task *get_running_task();

			/**
			 * must be called by the software inside the PendSV interrupt handler
			 */
			static void pendSV_handler();
			/**
			 * must be called by the software inside the SVC interrupt handler
			 */
			static void SVC_handler();

			/**
			 * Enters a Critical section. If the task is already in critical section, this function will just increment a counter.
			 * The critical section will be finished when the counter reaches 0 (the number of calls to OS::enter_critical()
			 * equals the number of calls to OS::exit_critical()).
			 */
			static void enter_critical();

			/**
			 * Exits a Critical section. If the task was already in critical section when it last entered it, this function will just decrement a counter.
			 * The critical section will be finished when the counter reaches 0 (the number of calls to OS::enter_critical()
			 * equals the number of calls to OS::exit_critical()).
			 */
			static void exit_critical();

			/**
			 * @return true if the task is currently in a critical section.
			 */
			static bool is_section_critical();

		};
//######################################################################################################################
//#                                            inline functions definitions                                            #
//######################################################################################################################

		inline OS::TaskCtrl::TaskCtrl(uint32_t priority, uint32_t *const stack, uint32_t stackSize) : // NOLINT
				// top_of_stask = stack + stack_size - 1;
				// top_of_stack = top_of_stack & ~((uint32_t)0x7) // ensure alignment
				// top_of_stack = top_of_stack - 17 //let place to store registers
				top_of_stack(reinterpret_cast<volatile uint32_t *>(
						((reinterpret_cast<const uint32_t>(stack) + (stackSize - 1) * sizeof(uint32_t))
						& ~0x7)
						- 17 * sizeof(uint32_t)
						)),
				stack_start(stack),
				prev_task(nullptr), next_task(nullptr), list(nullptr),
				priority(priority), timeout(0), event_mask(0),
				state(TaskState::DELETED), evt_clear_on_exit(0), evt_wait_all(0)
		{}

//______________________________________________________________________________________________________________________
//--------------------------------------------------- private methods --------------------------------------------------



//______________________________________________________________________________________________________________________
//--------------------------------------------------- public methods ---------------------------------------------------
		inline Task *OS::get_running_task()
		{
			return (Task *) _running_task;
		}
		inline bool OS::is_section_critical()
		{
			return _critical_section_counter > 0;
		}
		inline void OS::enter_critical()
		{
			++_critical_section_counter;
		}
	}
}
#endif //SOOL_OS_H
