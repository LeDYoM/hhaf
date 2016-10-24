#include <lib/include/events/eventreceiver.hpp>

namespace lib
{
	EventReceiver::EventReceiver() = default;
	EventReceiver::~EventReceiver() = default;

	void EventReceiver::setFilter(filter_event_t&& filterFunction)
	{
		m_filterFunction = filterFunction;
	}

	void EventReceiver::addSubscription(lib::events::EventSubscription &&nSubscription) noexcept
	{
		if (m_filterFunction) {
			const auto func(*(nSubscription.iData));
			*(nSubscription.iData) = [this, func](const lib::events::Event&ev) {
				if (m_filterFunction()) {
					func(ev);
				}
			};
		}
		m_subscriptions.emplace_back(std::move(nSubscription));
	}

	void EventReceiver::unsubscribeAll()
	{
		for (auto &subscription : m_subscriptions) {
			subscription.unsubscribe();
		}
		m_subscriptions.clear();
	}
}
