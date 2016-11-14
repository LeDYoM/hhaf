#ifndef LIB_EVENT_HPP__
#define LIB_EVENT_HPP__

#include <functional>
#include <list>
#include <lib/include/types.hpp>

namespace lib
{
	namespace events
	{
		class EventSubscription;
		class Event
		{
		public:
			using listener_t = std::function<void(const Event &)>;
			using listener_container_t = std::list<sptr<EventSubscription>>;

			virtual const listener_container_t &subscriptions() const noexcept = 0;
			virtual void dispatch() = 0;
		};

		class EventSubscription
		{
		public:
			using listener_t = Event::listener_t;

			virtual void subscribe() = 0;
			virtual void markForUnsubscription() = 0;
			listener_t listener{ nullptr };
		};

		template <typename T>
		class EventSubscriptionTemplate : public EventSubscription
		{
		public:
			EventSubscriptionTemplate(listener_t newListener)
			{
				listener = newListener;
				subscribe();
			}

			virtual void subscribe() override
			{
//				EventTemplate<T>::m_subscriptions.push_back(listener);
			}

			virtual void markForUnsubscription() override
			{
				m_markedForUnsubscription = true;
			}

			bool m_markedForUnsubscription{ false };
		};

		template <class T>
		class EventTemplate : public Event
		{
		public:
			virtual ~EventTemplate() = default;

			virtual const listener_container_t &subscriptions() const noexcept override { return m_subscriptions; }

			inline static auto subscribe(listener_t newListener)
			{
				sptr<EventSubscriptionTemplate<T>> m_ptr{ new EventSubscriptionTemplate<T>(newListener) };
				m_subscriptions.emplace_back(m_ptr);
				return m_ptr;
			}

			constexpr inline static void addSubscription(sptr<EventSubscriptionTemplate<T>> newListener)
			{
				m_subscriptions.emplace_back(newListener);
			}

			virtual void dispatch() override
			{
				if (!m_subscriptions.empty()) {
					for (const auto &subscription : m_subscriptions) {
						subscription->listener(*this);
					}
				}
			}

			static listener_container_t m_subscriptions;
		};

		template <typename T> Event::listener_container_t EventTemplate<T>::m_subscriptions;
	}
}
#endif
