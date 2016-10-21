#ifndef __LIB_CORE_EVENTSENDER_HPP__
#define __LIB_CORE_EVENTSENDER_HPP__

#include <lib/include/event.hpp>

#include <functional>
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
				using filter_event_t = std::function<bool()>;
				EventReceiver();
				virtual ~EventReceiver();

				void setFilter(filter_event_t&&);

				void addSubscription(lib::events::EventSubscription &&) noexcept;
				void unsubscribeAll();
			private:
				std::list<lib::events::EventSubscription> m_subscriptions;
				filter_event_t m_filterFunction;
			};
		}
	}
}
#endif
