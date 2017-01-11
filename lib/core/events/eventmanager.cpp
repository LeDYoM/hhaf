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
			while (!m_eventQueue.empty()) {
				logDebug("Event was still in queue: ", typeid(*(m_eventQueue.front())).name());
				m_eventQueue.pop();
			}
			logDestruct_NOPARAMS;
		}

		void EventManager::addEvent(sptr<lib::events::Event> event_)
		{
			m_eventQueue.emplace(std::move(event_));
		}

		void EventManager::postEvent(sptr<lib::events::Event> event_)
		{
			(m_processing?m_secondaryEventQueue:m_eventQueue).emplace(std::move(event_));
		}

		void EventManager::update()
		{
			if (!m_eventQueue.empty() || !m_secondaryEventQueue.empty()) {
				if (!m_secondaryEventQueue.empty()) {
					logDebug("Found ", m_secondaryEventQueue.size(), " events in the secondary event queue");
					do {
						m_eventQueue.emplace(m_secondaryEventQueue.front());
						m_secondaryEventQueue.pop();
					} while (!m_secondaryEventQueue.empty());
				}
				if (!m_eventQueue.empty()) {
					logDebug("Found ", m_eventQueue.size(), " events in the event queue");
					m_processing = true;
					do {
						m_eventQueue.front()->dispatch();
						if (m_resend) {
							m_secondaryEventQueue.emplace(m_eventQueue.front());
							m_resend = false;
						}
						m_eventQueue.pop();
					} while (!m_eventQueue.empty());
					m_processing = false;
				}
			}
		}
	}
}
