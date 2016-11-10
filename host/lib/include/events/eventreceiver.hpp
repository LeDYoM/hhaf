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
		EventReceiver();
		virtual ~EventReceiver();

		void addSubscription(lib::events::EventSubscription &&) noexcept;
		void unsubscribeAll();
	private:
		std::list<lib::events::EventSubscription> m_subscriptions;
	};
}
#endif
