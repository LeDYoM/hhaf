#ifndef __LIB_CORE_EVENTSENDER_HPP__
#define __LIB_CORE_EVENTSENDER_HPP__

#include <lib/include/event.hpp>

namespace lib
{
	namespace core
	{
		class EventManager;

		namespace events
		{
			class EventReceiver
			{
			public:
				EventReceiver &operator=(const EventReceiver &rh) = delete;
				virtual ~EventReceiver();

			private:
				EventReceiver(EventManager *const eventManager);
				EventManager  *const m_eventManager;
				friend class EventManager;
			};
		}
	}
}
#endif
