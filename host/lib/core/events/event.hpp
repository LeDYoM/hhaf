#ifndef LIB_EVENT_HPP__
#define LIB_EVENT_HPP__

#include <functional>
#include <list>

namespace lib
{
	namespace events
	{
		class Event
		{
		public:
			using listener_t = std::function<void(const Event &)>;
			using listener_container_t = std::list<listener_t>;

			virtual const listener_container_t &listeners() const noexcept = 0;
			virtual void dispatch() = 0;
		};

		class EventSubscription
		{
		public:
			using listener_t = Event::listener_t;
			using listener_container_t = Event::listener_container_t;
			using iterator_t = listener_container_t::iterator;

			virtual void subscribe() = 0;
			virtual void unsubscribe() = 0;
			virtual void markForUnsubscription() = 0;
		};

		template <typename T>
		class EventSubscriptionTemplate : public EventSubscription
		{
		public:
			using listener_container_t = Event::listener_container_t;
			using iterator_t = listener_container_t::iterator;
			EventSubscriptionTemplate(listener_t newListener)
				: listener{ newListener }
			{
				subscribe();
			}

			virtual void subscribe() override
			{
				EventTemplate<T>::m_listeners.push_back(listener);
				iData = std::prev(EventTemplate<T>::m_listeners.end());
			}

			virtual void unsubscribe() override
			{ 
//				EventTemplate<T>::m_listeners.erase(iData);
			}

			virtual void markForUnsubscription() override
			{
				m_markedForUnsubscription = true;
			}

			bool m_markedForUnsubscription{ false };
			listener_t listener{ nullptr };
			iterator_t iData;
		};

		template <class T>
		class EventTemplate : public Event
		{
		public:
			virtual ~EventTemplate() = default;

			virtual const listener_container_t &listeners() const noexcept override { return m_listeners; }

			constexpr inline static const listener_container_t &listenersStatic() noexcept { return m_listeners; }
			constexpr inline static auto subscribe(listener_t newListener)
			{
				return sptr<EventSubscriptionTemplate<T>>(new EventSubscriptionTemplate<T>{ newListener });
			}

			virtual void dispatch() override
			{
				if (!m_listeners.empty()) {
					for (const auto &listener : m_listeners) {
						listener(*this);
					}
				}
			}

			static listener_container_t m_listeners;
			static listener_container_t m_listenersToRemove;
		};

		template <typename T> Event::listener_container_t EventTemplate<T>::m_listeners;
		template <typename T> Event::listener_container_t EventTemplate<T>::m_listenersToRemove;

	}
}
#endif
