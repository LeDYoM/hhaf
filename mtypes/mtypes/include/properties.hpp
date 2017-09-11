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
		constexpr BasicProperty() noexcept : m_value{} {}
		constexpr BasicProperty(T iv) noexcept : m_value{ std::move(iv) } {}

		constexpr const T&operator()() const noexcept { return m_value; }
		constexpr const T &get() const noexcept { return m_value; }
		constexpr void set(const T&v) noexcept { m_value = v; }
		constexpr void operator=(const T&v) noexcept { set(v); }

	protected:
		T m_value;
	};

	template <typename T>
	class Property : public BasicProperty<T>
	{
	public:
		constexpr Property() noexcept : BasicProperty{}, m_callback{} {}
		constexpr Property(T iv) noexcept : BasicProperty{ std::move(iv) }, m_callback{} {}
		constexpr Property(callback_t c) noexcept : BasicProperty{}, m_callback{ std::move(c) } {}
		constexpr Property(T iv, callback_t c) noexcept : BasicProperty{ std::move(iv) }, m_callback{ std::move(c) } {}

		constexpr void setCallback(callback_t c) noexcept { m_callback = std::move(c); }
		constexpr void set(const T&v) noexcept { m_value = v; update(); }
		constexpr void operator=(const T&v) noexcept { set(v); }

		constexpr void update() { if (m_callback) m_callback(); }
	private:
		callback_t m_callback;
	};

	template <typename T>
	class PropertyObservable : public BasicProperty<T>
	{
	public:
		constexpr PropertyObservable() noexcept : BasicProperty{}, m_hasChanged{true} {}
		constexpr PropertyObservable(T iv) noexcept : BasicProperty{ std::move(iv) }, m_hasChanged{true} {}

		constexpr void set(const T&v) noexcept { m_hasChanged = true; m_value = v; }
		constexpr void operator=(const T&v) noexcept { set(v); }

		bool hasChanged() const noexcept { return m_hasChanged; }
		bool rr_hasChanged() const noexcept { const bool v{ m_hasChanged }; m_hasChanged = false; return v;	}

		constexpr void resetHasChanged() noexcept { m_hasChanged = true; }


	private:
		bool m_hasChanged;
	};

	template <typename class <typename T>>
	class PropertyWrapper
	{
	public:
		constexpr VirtualProperty(T&orig) noexcept : m_value{orig} {}

		constexpr const T &get() const noexcept { return m_value(); }
		constexpr void set(const T&v) noexcept { m_value.set(v); }

	protected:
		T m_value;
	};
}

#endif
