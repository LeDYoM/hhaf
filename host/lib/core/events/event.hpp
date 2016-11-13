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

		class EventSubscription
		{
		public:
			using listener_t = Event::listener_t;
			using listener_container_t = Event::listener_container_t;
			using iterator_t = listener_container_t::iterator;

			virtual void subscribe() = 0;
			virtual void unsubscribe() = 0;
			virtual void dettach() = 0;
		};

		template <typename T>
		class EventSubscriptionTemplate : public EventSubscription
		{
		public:
			using listener_container_t = Event::listener_container_t;
			using iterator_t = listener_container_t::iterator;
			EventSubscriptionTemplate(listener_t &&newListener) 
			{
				listener = std::move(newListener);
				subscribe();
			}

			virtual void subscribe() override
			{
				EventTemplate<T>::m_listeners.push_back(listener);
				iData = std::prev(EventTemplate<T>::m_listeners.end());
			}

			virtual void unsubscribe() override
			{ 
				EventTemplate<T>::m_listeners.erase(iData);
				iData = nullptr;
			}

			virtual void dettach()
			{
				(*it) = nullptr;
			}

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
			constexpr inline static EventSubscription subscribe(listener_t &&newListener)
			{
				m_listeners.emplace_back(std::move(newListener));
				return EventSubscription{ std::prev(m_listeners.end()), m_listeners };
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

			static listener_container_t m_listeners;
			static listener_container_t m_listenersToRemove;
		};

		template <typename T> Event::listener_container_t EventTemplate<T>::m_listeners;
		template <typename T> Event::listener_container_t EventTemplate<T>::m_listenersToRemove;

	}
}
#endif
