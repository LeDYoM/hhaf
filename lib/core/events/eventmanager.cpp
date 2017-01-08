#include "eventmanager.hpp"
#include "eventreceiver.hpp"

#include <lib/core/log.hpp>

namespace lib
{
	namespace core
	{
		EventManager::EventManager()
		{
			logConstruct_NOPARAMS;
		}

		EventManager::~EventManager()
		{
			logDebug("Going to destroy event manager...");
			while (!eventQueue.empty()) {
				logDebug("Event was still in queue: ", typeid(*(eventQueue.front())).name());
				eventQueue.pop();
			}
			logDestruct_NOPARAMS;
		}

		void EventManager::addEvent(sptr<lib::events::Event> event_)
		{
			eventQueue.emplace(std::move(event_));
		}

		void EventManager::update()
		{
			if (!eventQueue.empty()) {
				logDebug("Found ", eventQueue.size(), " events in the event queue");
				do {
					eventQueue.front()->dispatch();
					eventQueue.pop();
				} while (!eventQueue.empty());
			}
		}
	}
}
