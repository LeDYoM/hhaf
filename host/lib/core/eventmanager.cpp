#include "eventmanager.hpp"
#include "events/eventsender.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{

		EventManager::EventManager(AppController *const appController)
			: AppService{ appController }
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		EventManager::~EventManager()
		{
			LOG_DEBUG("Going to destroy event manager...");
			while (!eventQueue.empty())
			{
				LOG_DEBUG("Event was still in queue: " << typeid(eventQueue.front()).name());
				eventQueue.pop();
			}
			LOG_DESTRUCT_NOPARAMS;
		}

		sptr<events::EventSender> EventManager::newEventSender()
		{
			auto temp = sptr<events::EventSender>(new events::EventSender(this));
			m_eventsenders.push_back(temp);
			return temp;
		}

		void EventManager::addEvent(uptr<lib::events::Event> event_)
		{
			eventQueue.push(sptr<lib::events::Event>(std::move(event_)));
		}

		bool EventManager::empty()
		{
			return eventQueue.empty();
		}
	}
}