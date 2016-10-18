#include "eventmanager.hpp"
#include "events/eventsender.hpp"
#include "log.hpp"

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
			eventQueue.push(std::move(event_));
		}

		bool EventManager::empty()
		{
			return eventQueue.empty();
		}
	}
}