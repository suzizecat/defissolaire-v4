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
#include "../include/events.h"
#include "../include/task.h"
#include "../include/os.h"

namespace sool
{
	namespace os
	{

		void EventGroup::add_task(OS::TaskCtrl *task, uint32_t ticks_timeout)
		{
			OS::enter_critical();
			OS::_task_remove(task);
			OS::TaskCtrl *prev = nullptr;
			OS::TaskCtrl *next = _waiting_tasks;

			while (next != nullptr && ((next->timeout < ticks_timeout) ||
									   (next->timeout == ticks_timeout && next->priority <= task->priority))) {

				if (ticks_timeout != Task::INFINITE_DELAY)
					ticks_timeout -= next->timeout;

				prev = next;
				next = next->next_task;
			}
			if (prev != nullptr)
				prev->next_task = task;
			else
				_waiting_tasks = task;

			task->prev_task = prev;
			task->next_task = next;
			next->prev_task = task;
			task->list = &_waiting_tasks;
			task->timeout = ticks_timeout;
			task->state = TaskState::WAITING_EVENT;
			OS::exit_critical();
		}

		void EventGroup::fire_events(const uint32_t mask)
		{
			_value |= mask;
			OS::TaskCtrl *task = _waiting_tasks;
			uint32_t clear = 0;
			while (task != nullptr) {
				uint32_t match = task->event_mask & _value;
				if (match != 0) {
					if (task->evt_clear_on_exit) clear |= match;
					task->event_mask &= ~match;
					if ((task->event_mask == 0) || (task->evt_wait_all == 0)) {
						OS::_set_task_ready(task);
					}
				}
				task = task->next_task;
			}
			if (clear != 0) {
				clear_events(clear);
			}
		}
	}
}
