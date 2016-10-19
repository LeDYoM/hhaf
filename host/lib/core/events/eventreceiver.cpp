#include "eventreceiver.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			EventReceiver::EventReceiver() = default;
			EventReceiver::~EventReceiver() = default;

			void EventReceiver::addSubscription(lib::events::EventSubscription &&nSubscription)
			{
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
	}
}
