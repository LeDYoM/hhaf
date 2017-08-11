#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "compconfig.hpp"
#include <functional>

namespace lib
{
	template <typename T>
	class Property
	{
	public:
		using callback_t = std::function<void()>;

		constexpr Property(T iv = {}, callback_t c = {}) : m_value{ std::move(iv) }, m_callback{ std::move(c) } {}

		constexpr void setCallback(callback_t c) noexcept { m_callback = std::move(c); }

		const T &get() const noexcept { return m_value; }
		void set(const T&v) { m_value = std::move(v); update(); }
		constexpr void operator=(const T&v) { set(v); }
		constexpr const T&operator()() const noexcept { return get(); }

		constexpr void update() { if (m_callback) m_callback(); }
	private:
		T m_value;
		callback_t m_callback;
	};
}

#endif
