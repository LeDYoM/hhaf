#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "compconfig.hpp"
#include <functional>

namespace lib
{
	using callback_t = std::function<void()>;

	template<typename T, void (T::*sm)()>
	constexpr callback_t lambdaToMethod(T& d) {
		return [&d]() {(d.*sm)(); };
	}

	template <typename T>
	class Property
	{
	public:
		constexpr Property() noexcept : m_value{ }, m_callback{ } {}
		constexpr Property(T iv) noexcept : m_value{ std::move(iv) }, m_callback{ } {}
		constexpr Property(callback_t c) noexcept : m_value{ }, m_callback{ std::move(c) } {}
		constexpr Property(T iv, callback_t c) noexcept : m_value{ std::move(iv) }, m_callback{ std::move(c) } {}

		constexpr void setCallback(callback_t c) noexcept { m_callback = std::move(c); }

		constexpr const T &get() const noexcept { return m_value; }
		constexpr void set(const T&v) noexcept { m_value = v; update(); }
		constexpr void set(T&&v) noexcept { m_value = std::move(v); update(); }
		constexpr void operator=(const T&v) noexcept { set(v); }
		constexpr void operator=(T&&v) noexcept { set(std::move(v)); }
		constexpr const T&operator()() const noexcept { return m_value; }

		constexpr void update() { if (m_callback) m_callback(); }
	private:
		T m_value;
		callback_t m_callback;
	};
}

#endif
