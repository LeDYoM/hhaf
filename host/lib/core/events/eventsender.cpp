#include "eventsender.hpp"
#include "../eventmanager.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			EventSender::EventSender(EventManager *const eventManager) : m_eventManager{ eventManager }
			{

			}

			EventSender::~EventSender()
			{

			}

			void EventSender::sendEvent(uptr<lib::events::Event> event_)
			{
				m_eventManager->addEvent(std::move(event_));
			}

		}
	}
}
