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
		template <typename T>
		class EventTemplate : public Event
		{
		public:
			constexpr EventTemplate() {}
			virtual ~EventTemplate() { }

			static const listener_container_t &listeners() noexcept { return m_listeners; }
			static bool subscribe(listener_t newListener)
			{
				m_listeners.emplace(std::move(newListener));
			}
		private:
			static listener_container_t m_listeners;
		};
	}
}
#endif
