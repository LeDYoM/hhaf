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

		void EventManager::update()
		{
			if (!eventQueue.empty()) {
				LOG_DEBUG("Found " << eventQueue.size() << " events in the event queue");
				do {
					const auto event(eventQueue.front());
					if (!event->listeners().empty()) {
						for (const auto &subscriber : event->listeners()) {
							subscriber(*event);
						}
					}
					eventQueue.pop();
				} while (!eventQueue.empty());
			}
		}

		bool EventManager::empty() const noexcept
		{
			return eventQueue.empty();
		}
	}
}