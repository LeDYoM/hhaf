#ifndef __LIB_CORE_EVENTSENDER_HPP__
#define __LIB_CORE_EVENTSENDER_HPP__

#include <lib/include/event.hpp>
#include <list>

namespace lib
{
	namespace core
	{
		namespace events
		{
			class EventReceiver
			{
			public:
				EventReceiver();
				virtual ~EventReceiver();

				void addSubscription(lib::events::EventSubscription &&) noexcept;
				void unsubscribeAll();
			private:
				std::list<lib::events::EventSubscription> m_subscriptions;
			};
		}
	}
}
#endif
