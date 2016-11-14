#include "eventreceiver.hpp"

namespace lib
{
	EventReceiver::EventReceiver() = default;


	EventReceiver::~EventReceiver()
	{
		unsubscribeAll();
		m_subscriptions.clear();
	}

	void EventReceiver::addSubscription(sptr<lib::events::EventSubscription> &&nSubscription) noexcept
	{
		m_subscriptions.emplace_back(std::move(nSubscription));
	}

	void EventReceiver::unsubscribeAll()
	{
		for (auto &subscription : m_subscriptions) {
			subscription->markForUnsubscription();
		}
//		m_subscriptions.clear();
	}
}
