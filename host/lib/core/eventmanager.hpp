#ifndef __LIB_EVENTMANAGER_HPP__
#define __LIB_EVENTMANAGER_HPP__

#include "appservice.hpp"
#include <lib/include/event.hpp>
#include <lib/include/types.hpp>
#include "vecsptr.hpp"
#include <queue>
#include <functional>

namespace lib
{
	namespace core
	{
		namespace events
		{
			class EventSender;
		}
		class EventManager : public AppService
		{
		public:
			EventManager(AppController *const appController);
			virtual ~EventManager();

			sptr<events::EventSender> newEventSender();
			virtual void addEvent(uptr<lib::events::Event> event_);
		private:
			virtual bool empty();
			friend class events::EventSender;

			std::queue<sptr<lib::events::Event>> eventQueue;
			VecSPtr<events::EventSender> m_eventsenders;
		};
	}
}
#endif
