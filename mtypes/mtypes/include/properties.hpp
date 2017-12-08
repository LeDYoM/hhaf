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
		constexpr BasicProperty() noexcept = default;
		constexpr BasicProperty(T iv) noexcept : m_value{ std::move(iv) } {}

		constexpr const T&operator()() const noexcept { return m_value; }
		constexpr const T &get() const noexcept { return m_value; }
		constexpr void set(const T&v) noexcept { m_value = v; }
		constexpr void operator=(const T&v) noexcept { set(v); }

	protected:
		T m_value{};
	};

	template <typename T>
	class Property : public BasicProperty<T>
	{
        using BaseClass = BasicProperty<T>;
	public:
		constexpr Property() noexcept = default;
		constexpr Property(T iv) noexcept : BaseClass{ std::move(iv) }, m_callback{} {}
		constexpr Property(callback_t c) noexcept : BaseClass{}, m_callback{ std::move(c) } {}
		constexpr Property(T iv, callback_t c) noexcept : BaseClass{ std::move(iv) }, m_callback{ std::move(c) } {}

		constexpr void setCallback(callback_t c) noexcept { m_callback = std::move(c); }
		constexpr void set(const T&v) noexcept { BaseClass::m_value = v; m_hasChanged = true; update(); }
		constexpr void operator=(const T&v) noexcept { set(v); }

		constexpr void update() { if (m_callback) m_callback(); }

		bool hasChanged() const noexcept { return m_hasChanged; }
		bool rr_hasChanged() const noexcept { const bool v{ m_hasChanged }; m_hasChanged = false; return v; }

		constexpr void resetHasChanged() noexcept { m_hasChanged = false; }

	private:
		callback_t m_callback{};
		bool m_hasChanged{ true };
	};
}

#endif
