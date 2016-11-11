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
			virtual bool lock(const bool) = 0;
			virtual void dispatch() = 0;
		};

		class EventSubscription final
		{
		public:
			using listener_container_t = Event::listener_container_t;
			using iterator_t = listener_container_t::iterator;
			EventSubscription(iterator_t it, listener_container_t & listeners) : iData{ it }, m_eventListeners{ listeners } {}
			EventSubscription() = delete;
			EventSubscription(const EventSubscription&) = default;
			EventSubscription &operator=(const EventSubscription&) = default;
			EventSubscription(EventSubscription&&) = default;
			EventSubscription &operator=(EventSubscription&&) = default;
			~EventSubscription() = default;

			inline void unsubscribe() { m_eventListeners.erase(iData);	}

			iterator_t iData;

		private:
			Event::listener_container_t &m_eventListeners;
		};

		template <class T>
		class EventTemplate : public Event
		{
		public:
			constexpr EventTemplate() {}
			virtual ~EventTemplate() { }

			virtual const listener_container_t &listeners() const noexcept override { return m_listeners; }

			inline static const listener_container_t &listenersStatic() noexcept { return m_listeners; }
			inline static EventSubscription subscribe(listener_t &&newListener)
			{
				m_listeners.emplace_back(newListener);
				return EventSubscription{ std::prev(m_listeners.end()), m_listeners };
			}

			inline static void unsubscribe(const EventSubscription&evs)
			{
				m_listeners.erase(evs.iData);
			}

			virtual void dispatch() override
			{
				if (!m_listeners.empty()) {
					auto listenersCopy(m_listeners);
					for (const auto &listener : listenersCopy) {
						listener(*this);
					}
					std::swap(listenersCopy, m_listeners);
					listenersCopy.clear();
				}
			}

			virtual bool lock(const bool nState) override
			{
				const bool prev{ m_locked };
				m_locked = nState;
				return prev;
			}
		private:
			static listener_container_t m_listeners;
			static bool m_locked;
		};

		template <typename T> Event::listener_container_t EventTemplate<T>::m_listeners;
		template <typename T> bool EventTemplate<T>::m_locked = false;

	}
}
#endif
