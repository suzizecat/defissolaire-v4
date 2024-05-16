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
#include "../include/task.h"
#include "../include/os.h"

namespace sool
{
	namespace os
	{

		static void task_exit()
		{
			OS::get_running_task()->kill();
			for (;;) // go there only if a critical section has not been closed before finishing the task
				OS::exit_critical();

		}

		Task::Task(void (*task_function)(void *parameters), uint32_t priority, uint32_t *stack, uint32_t stackSize,
				   void *parameters) :
				_control(priority, stack, stackSize)
		{
			// Simulate the stack frame as it would be created by a context switch interrupt.

			_control.top_of_stack[16] = 0x01000000; //xPSR : init T to 1
			_control.top_of_stack[15] = reinterpret_cast<uint32_t>(task_function) & ~((uint32_t)0x00000001); // PC
			_control.top_of_stack[14] = reinterpret_cast<uint32_t>(task_exit); // LR
			//control.top_of_stack[13->10] : R12, R3, R2, R1.
			_control.top_of_stack[9] = reinterpret_cast<uint32_t>(parameters); // R0
			_control.top_of_stack[8] = ((~0) << 5) // EXC_RETURN[31:5] = 1
											  | (1 << 3) // EXC_RETURN[3] = 1 : return to thread mode
											  | (1 << 4) // EXC_RETURN[4] = 1 : exception return uses non-floating point state...
											  | (1 << 2) // EXC_RETURN[2] = 1 : ...from the PSP and execution uses PSP after return
											  | (1 << 0);
			//control.top_of_stack[7->0] : R11, R10, R9, R8, R7, R6, R5, R4.
			// debug values
			_control.top_of_stack[13] = 0x12;
			_control.top_of_stack[12] = 3;
			_control.top_of_stack[11] = 2;
			_control.top_of_stack[10] = 1;
			_control.top_of_stack[7] = 11;
			_control.top_of_stack[6] = 10;
			_control.top_of_stack[5] = 9;
			_control.top_of_stack[4] = 8;
			_control.top_of_stack[3] = 7;
			_control.top_of_stack[2] = 6;
			_control.top_of_stack[1] = 5;
			_control.top_of_stack[0] = 4;
		}
		//TODO Dynamic task constructor
		//DynamicTask::DynamicTask(void (*task_function)(), uint32_t priority, uint32_t stackSize)
	}
}
