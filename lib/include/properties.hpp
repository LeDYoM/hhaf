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
		constexpr Property(T iv = {}, callback_t c = {}) noexcept : m_value{ std::move(iv) }, m_callback{ std::move(c) } {}
		Property(const Property&) = delete;
		Property& operator=(const Property&) = delete;

		constexpr inline const T &operator()() const noexcept { return m_value; }
		inline void setCallback(callback_t c) noexcept { m_callback = std::move(c); }
		constexpr inline const T &get() const noexcept { return m_value; }
		inline void set(const T&v) { m_value = v; update(); }
		inline void set(T&&v) { m_value = std::move(v); update(); }
		inline Property &operator=(const T&v) { set(v); return *this; }
		inline Property &operator=(T&&v) { set(std::move(v)); return *this; }

		inline void update() { if (m_callback) m_callback(); }
	private:
		T m_value;
		callback_t m_callback;
	};

	template <typename T>
	class ForwardProperty
	{
	public:
		constexpr ForwardProperty() noexcept {}
		constexpr ForwardProperty(Property<T> *const iv) noexcept : m_value{ iv } {}
		ForwardProperty(const ForwardProperty&) = delete;
		ForwardProperty& operator=(const ForwardProperty&) = delete;

		constexpr inline const T &operator()() const noexcept { return (*m_value)(); }
		inline void setForwardProperty(Property<T> *const p) noexcept { m_value = p; }
		constexpr inline const T &get() const noexcept { return (*m_value).get(); }
		inline void set(const T&v) { (*m_value) = v; }
		inline void set(T&&v) { (*m_value) = std::move(v); }
		inline ForwardProperty &operator=(const T&v) { set(v); return *this; }
		inline ForwardProperty &operator=(T&&v) { set(std::move(v)); return *this; }
		inline Property<T> *const innerProperty() const { return m_value; }
	private:
		Property<T> *m_value{ nullptr };
	};

	template <typename T>
	class ReadOnlyRefProperty
	{
	public:
		constexpr ReadOnlyRefProperty(const T&p) noexcept : m_value{ p } {}
		constexpr inline const T &get() const noexcept { return m_property; }
		constexpr inline const T &operator()() const noexcept { return m_property; }

	private:
		const T &m_value;
	};
}

#endif
