#ifndef LIB_EVENTS_EVENTSENDER_HPP__
#define LIB_EVENTS_EVENTSENDER_HPP__

#include "event.hpp"

#include <functional>
#include <list>

namespace lib
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
#endif
