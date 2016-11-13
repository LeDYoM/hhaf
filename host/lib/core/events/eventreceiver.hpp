#ifndef LIB_EVENTS_EVENTRECEIVER_INCLUDE_HPP__
#define LIB_EVENTS_EVENTRECEIVER_INCLUDE_HPP__

#include "event.hpp"
#include <lib/include/types.hpp>
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
		std::list<sptr<lib::events::EventSubscription>> m_subscriptions;
	};
}
#endif
