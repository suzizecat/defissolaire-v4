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
#ifndef SOOL_OS_EVENTS_H
#define SOOL_OS_EVENTS_H

#include <cstdint>
#include "os.h"

namespace sool
{
	namespace os
	{
		class EventGroup
		{
		private:
			uint32_t _value;
			OS::TaskCtrl *_waiting_tasks;
			EventGroup *_previous_event_group;
			EventGroup *_next_event_group;

			void add_task(OS::TaskCtrl *task, uint32_t ticks_timeout);

			friend class OS;

			friend class Task;

		public:
			void fire_events(const uint32_t mask); //NOLINT
			void clear_events(const uint32_t mask); //NOLINT
			void tick();
		};

		inline void EventGroup::tick()
		{
			OS::TaskCtrl *task = _waiting_tasks;

			while (task != nullptr && task->timeout == 0) {
				_waiting_tasks = task->next_task;            // move list pointer from 1st element to 2nd element.
				OS::_set_task_ready(task);                // move task from _delayed_tasks_list to _ready_tasks_list
				task = _waiting_tasks;                        // change local variable to new first element of list
			}
			if (task != nullptr) {
				if (task->timeout != ~0u)                    // max value (2^32 - 1): waiting for an infinite time
					task->timeout--;
			}
		}

		inline void EventGroup::clear_events(const uint32_t mask)
		{
			_value &= ~mask;
		}
	}
}

#endif //SOOL_OS_EVENTS_H
