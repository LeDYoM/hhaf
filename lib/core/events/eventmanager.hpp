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

			void addEvent(sptr<lib::events::Event> event_);
			void postEvent(sptr<lib::events::Event> event_);
			void update();
		private:
			std::queue<sptr<events::Event>> m_eventQueue;
			std::queue<sptr<events::Event>> m_secondaryEventQueue;
			bool m_processing{ false };
		};
	}
}
#endif
