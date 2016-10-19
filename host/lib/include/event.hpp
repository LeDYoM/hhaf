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
		};

		class EventSubscription
		{
		public:
			using iterator_t = Event::listener_container_t::iterator;
			EventSubscription(iterator_t it, Event::listener_container_t & listeners) : iData{ it }, m_eventListeners{ listeners } {}
			iterator_t iData;
			EventSubscription() = default;
			EventSubscription(const EventSubscription&) = default;
			EventSubscription &operator=(const EventSubscription&) = default;
			EventSubscription(EventSubscription&&) = default;
			EventSubscription &operator=(EventSubscription&&) = default;
			~EventSubscription() = default;

			Event::listener_container_t &m_eventListeners;
		};

		template <class T>
		class EventTemplate : public Event
		{
		public:
			constexpr EventTemplate() {}
			virtual ~EventTemplate() { }

			virtual const listener_container_t &listeners() const noexcept { return m_listeners; }

			static const listener_container_t &listenersStatic() noexcept { return m_listeners; }
			static EventSubscription subscribe(listener_t &&newListener)
			{
				m_listeners.emplace_back(std::move(newListener));
				return std::move(EventSubscription{ std::prev(m_listeners.end()), m_listeners });
			}

			static void unsubscribe(const EventSubscription&evs)
			{
				m_listeners.erase(evs.iData);
			}
		private:
			static listener_container_t m_listeners;
		};

		template <typename T> Event::listener_container_t EventTemplate<T>::m_listeners;
	}
}
#endif
