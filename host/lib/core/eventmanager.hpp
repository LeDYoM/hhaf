#ifndef __LIB_EVENTMANAGER_HPP__
#define __LIB_EVENTMANAGER_HPP__

#include "appservice.hpp"
#include <lib/include/events/event.hpp>
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
			void update();
		private:
			bool empty() const noexcept;
			std::queue<sptr<events::Event>> eventQueue;
		};
	}
}
#endif
