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
			using listener_t = std::function<bool(const Event &)>;
			using listener_container_t = std::list<listener_t>;

		};
		template <class T>
		class EventTemplate : public Event
		{
		public:
			constexpr EventTemplate() {}
			virtual ~EventTemplate() { }

			static const listener_container_t &listeners() noexcept { return m_listeners; }
			static bool subscribe(listener_t newListener)
			{
				m_listeners.emplace_back(std::move(newListener));
				return true;
			}
		private:
			static listener_container_t m_listeners;
		};

		template <typename T> Event::listener_container_t EventTemplate<T>::m_listeners;
	}
}
#endif
