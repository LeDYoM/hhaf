#ifndef __LIB_EVENTMANAGER_HPP__
#define __LIB_EVENTMANAGER_HPP__

#include "event.hpp"
#include <lib/core/appservice.hpp>
#include <lib/include/types.hpp>
#include <queue>

namespace lib
{
	namespace core
	{
		class EventManager : public AppService
		{
		public:
			EventManager();
			~EventManager();

			void addEvent(sptr<events::Event> event_);
			void postEvent(sptr<events::Event> event_);
			void update();
			inline void resendCurrentEvent() noexcept { m_resend = true; }
		private:
			std::queue<sptr<events::Event>> m_eventQueue;
			std::queue<sptr<events::Event>> m_secondaryEventQueue;
			bool m_processing{ false };
			bool m_resend{ false };
		};
	}
}
#endif
