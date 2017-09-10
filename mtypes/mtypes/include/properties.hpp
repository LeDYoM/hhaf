#pragma once

#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "function.hpp"

namespace lib
{
	using callback_t = function<void()>;

	template<typename T, void (T::*sm)()>
	constexpr callback_t lambdaToMethod(T& d) {
		return [&d]() {(d.*sm)(); };
	}

	template <typename T>
	class BasicProperty
	{
	public:
		constexpr BasicProperty(T iv) noexcept : m_value{ std::move(iv) } {}
		constexpr const T &get() const noexcept { return m_value; }
		constexpr const T&operator()() const noexcept { return m_value; }
		constexpr void set(const T&v) noexcept { m_value = v; }
		constexpr void operator=(const T&v) noexcept { m_value = v; }

	private:
		T m_value;
	};

	template <typename T>
	class Property : public BasicProperty<T>
	{
	public:
		constexpr Property(T iv = {}, callback_t c = {}) noexcept : BasicProperty{ std::move(iv) }, m_callback{ std::move(c) } {}
		constexpr Property(callback_t c) noexcept : BasicProperty{ {} }, m_callback{ std::move(c) } {}

		constexpr void setCallback(callback_t c) noexcept { m_callback = std::move(c); }

		constexpr void set(const T&v) noexcept { BasicProperty::set(v); update(); }
		constexpr void operator=(const T&v) noexcept { BasicProperty::set(v); }

		constexpr void update() { if (m_callback) m_callback(); }
	private:
		callback_t m_callback;
	};

	template <typename T>
	class Property2 : public BasicProperty<T>
	{
	public:
		constexpr Property2(T iv) noexcept : BasicProperty{ std::move(iv) } {}

		constexpr void set(const T&v) noexcept { m_value = v; m_modified = true; }
		constexpr void operator=(const T&v) noexcept { set(v); }

		constexpr bool isModified() const noexcept { return m_modified; }
		constexpr bool getResetModified() noexcept { const bool value{ m_modified }; m_modified = false; return value; }
	private:
		bool m_modified{ true };
		callback_t m_callback;
	};
}

#endif
