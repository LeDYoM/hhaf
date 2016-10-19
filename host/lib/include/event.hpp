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

		template <typename T>
		class EventSubscriptionTemplate
		{
		public:
			using iterator_t = Event::listener_container_t::iterator;
			EventSubscriptionTemplate(iterator_t it) : iData{ it } {}
			iterator_t iData;
			EventSubscriptionTemplate() = default;
			EventSubscriptionTemplate(const EventSubscriptionTemplate&) = default;
			EventSubscriptionTemplate &operator=(const EventSubscriptionTemplate&) = default;
			EventSubscriptionTemplate(EventSubscriptionTemplate&&) = default;
			EventSubscriptionTemplate &operator=(EventSubscriptionTemplate&&) = default;
			~EventSubscriptionTemplate() = default;
		};

		template <class T>
		class EventTemplate : public Event
		{
		public:
			constexpr EventTemplate() {}
			virtual ~EventTemplate() { }

			virtual const listener_container_t &listeners() const noexcept { return m_listeners; }

			static const listener_container_t &listenersStatic() noexcept { return m_listeners; }
			static EventSubscriptionTemplate subscribe(listener_t &&newListener)
			{
				m_listeners.emplace_back(std::move(newListener));
				return std::move(EventSubscriptionTemplate{ std::prev(m_listeners.end()) });
			}

			static void unsubscribe(const EventSubscriptionTemplate&evs)
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
