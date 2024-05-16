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
#ifndef SOOL_OS_TASK_H
#define SOOL_OS_TASK_H

#include <cstdint>
#include "os.h"
#include "events.h"

namespace sool
{
	namespace os
	{

		class Task
		{
		private:
			/**
			 * For the use of the OS only.
			 */
			OS::TaskCtrl _control;

			friend class OS;

			friend class EventGroup;

		public:
			static constexpr uint32_t INFINITE_DELAY = ~0u;

		protected:
			Task(void (*task_function)(void *parameters), uint32_t priority, uint32_t *stack, uint32_t stackSize,
				 void *parameters);

		public:

			/**
			 * Set the task ready to be started/resumed.
			 * @param fromEvent
			 */
			void wake_up();

			/**
			 * Completely remove the task from the OS after switching to the next task
			 */
			void kill();

			/**
			 * Pause the task the specified amount of time, in ticks. If the time is not specified
			 * or equal to Task::INFINITE_DELAY, the task will be paused until explicitly asked to wake up.
			 * @param ticks_to_wait number of ticks to wait. default is Task::INFINITE_DELAY
			 */
			void wait(uint32_t ticks_to_wait = INFINITE_DELAY);

			/**
			 * Wait until the specified mask match events in the specified event group. <br/>
			 *
			 * If all_events is set to true, the task will only be woken up if all bits match at least one event. <br/>
			 * Otherwise, the task will be woken up for every event happening. <br/>
			 *
			 * When the task is woken up from event, it goes to the ready tasks list.
			 * If events occur before the task actually wakes up, it might be missed. You can check the uncleared
			 * events by calling event_group.get_value()
			 *
			 * @param evt_grp - the event group in which the eventw will be captured
			 * @param mask - a mask where each bit represent an event to capture
			 * @param all_events - whether all the events of the mask or only one must be captured to wake up the task.
			 * @param ticks_timeout - maximum number of ticks to wait. default is Task::INFINITE_DELAY
			 */
			void wait(EventGroup *evt_grp, uint32_t mask, bool all_events, bool clear_on_exit,
					  uint32_t ticks_timeout = INFINITE_DELAY);
		};

		class StaticTask : public Task
		{
		private:
			/**
			 * This function is used by the library as the function that loops the function provided for the task
			 */
			//static void looper(void *parameters);

		public:
			StaticTask(void (*task_function)(void *parameters), uint32_t priority, uint32_t *stack, uint32_t stackSize, void *parameters);
		};

		class DynamicTask : public Task
		{
		public:
			DynamicTask(void (*task_function)(void *parameters), uint32_t priority, uint32_t stackSize,
						void *parameters);
		};

//######################################################################################################################
//#                                            inline functions definition                                             #
//######################################################################################################################

//______________________________________________________________________________________________________________________
//-------------------------------------------- derived classes constructors --------------------------------------------
		inline StaticTask::StaticTask(void (*task_function)(void *parameters), uint32_t priority, uint32_t *stack, uint32_t stackSize, void *parameters) :
				Task(task_function, priority, stack, stackSize, parameters)
		{

		}

//______________________________________________________________________________________________________________________
//--------------------------------------------------- wake_up, kill ----------------------------------------------------
		inline void Task::wake_up()
		{
			OS::_set_task_ready(&(this->_control));
		}

		inline void Task::kill()
		{
			OS::_task_remove(&(this->_control));
			this->_control.state = TaskState::DELETED;
			if (this == OS::get_running_task())
				OS::_request_task_switch();
		}
//______________________________________________________________________________________________________________________
//--------------------------------------------------- wait functions ---------------------------------------------------
		inline void Task::wait(uint32_t ticks_to_wait)
		{
			OS::_task_wait(&(this->_control), ticks_to_wait);
		}

		inline void Task::wait(EventGroup *evt_grp, uint32_t mask, bool all_events, bool clear_on_exit,
							   uint32_t ticks_timeout)
		{
			this->_control.event_mask = mask;
			this->_control.evt_clear_on_exit = clear_on_exit;
			this->_control.evt_wait_all = all_events;
			evt_grp->add_task(&(this->_control), ticks_timeout);
		}
	};
};
#endif //SOOL_OS_TASK_H
