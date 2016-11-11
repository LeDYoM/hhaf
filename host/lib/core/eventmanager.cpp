#include "eventmanager.hpp"
#include "log.hpp"

#include <lib/include/events/eventreceiver.hpp>

namespace lib
{
	namespace core
	{
		EventManager::EventManager()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		EventManager::~EventManager()
		{
			LOG_DEBUG("Going to destroy event manager...");
			while (!eventQueue.empty())
			{
				LOG_DEBUG("Event was still in queue: " << typeid(*(eventQueue.front())).name());
				eventQueue.pop();
			}
			LOG_DESTRUCT_NOPARAMS;
		}

		void EventManager::addEvent(sptr<lib::events::Event> event_)
		{
			eventQueue.emplace(std::move(event_));
		}

		void EventManager::update()
		{
			if (!eventQueue.empty()) {
				LOG_DEBUG("Found " << eventQueue.size() << " events in the event queue");
				do {
					eventQueue.front()->dispatch();
					eventQueue.pop();
				} while (!eventQueue.empty());
			}
		}
	}
}
