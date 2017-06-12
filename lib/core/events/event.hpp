#ifndef LIB_EVENT_HPP__
#define LIB_EVENT_HPP__

#include <functional>
#include <list>
#include <mtypes/include/types.hpp>

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

		template <typename T>
		constexpr const std::remove_reference_t<T>& eventAs(const Event&ev)
		{
			return dynamic_cast<const std::remove_reference_t<T>&>(ev);
		}

		class EventSubscription
		{
		public:
			using listener_t = Event::listener_t;
			EventSubscription(const listener_t &newListener) : listener{ newListener } {	}

			void markForUnsubscription() noexcept
			{
				m_markedForUnsubscription = true;
			}

			bool m_markedForUnsubscription{ false };
			const listener_t listener;
		};

		template <class T>
		class EventTemplate : public Event
		{
		public:
			using listener_container_t = Event::listener_container_t;
			virtual ~EventTemplate() = default;

			virtual const listener_container_t &subscriptions() const noexcept override { return m_subscriptions; }

			inline static auto subscribe(const listener_t &newListener)
			{
				auto m_ptr( msptr<EventSubscription>(newListener) );
				m_subscriptions.push_back(m_ptr);
				return m_ptr;
			}

			inline static void unsubscribeMarked()
			{
				for (auto it = m_subscriptions.begin(); it != m_subscriptions.end();) {
					auto itTemp(it++);
					if ((*itTemp)->m_markedForUnsubscription) {
						(*itTemp)->m_markedForUnsubscription = false;
						m_subscriptions.erase(itTemp);
					}
				}
			}

			virtual void dispatch() override
			{
				if (!m_subscriptions.empty()) {
					m_dispatching = true;
					bool unsubsciptionNeeded = false;
					for (const auto &subscription : m_subscriptions) {
						subscription->listener(*this);

						if (subscription->m_markedForUnsubscription) {
							unsubsciptionNeeded = true;
						}
					}
					m_dispatching = false;
					if (unsubsciptionNeeded) {
						unsubscribeMarked();
					}
				}
			}
			static bool m_dispatching;
			static listener_container_t m_subscriptions;
		};

		template <typename T> bool EventTemplate<T>::m_dispatching;
		template <typename T> Event::listener_container_t EventTemplate<T>::m_subscriptions;
	}
}
#endif
