#ifndef __LIB_EVENTMANAGER_HPP__
#define __LIB_EVENTMANAGER_HPP__

#include "appservice.hpp"
#include <lib/include/event.hpp>
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
		private:
			bool empty();
			std::queue<sptr<lib::events::Event>> eventQueue;
		};
	}
}
#endif
