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
	class Property<Property<T>>
	{
	public:
		using callback_t = std::function<void(const T &newValue)>;
		constexpr Property(Property<T> &iv, callback_t c = {}) noexcept : m_value{ iv }, m_callback{ std::move(c) } {}
		Property(const Property&) = delete;
		Property& operator=(const Property&) = delete;

		constexpr inline const T &operator()() const noexcept { return m_value; }
		inline void setCallback(callback_t c) noexcept { m_callback = std::move(c); }
		constexpr inline const T &get() const noexcept { return m_value; }
		inline void set(const T&v) { m_value = v; if (m_callback) m_callback(); }
		inline void set(T&&v) { m_value = std::move(v); if (m_callback) m_callback(); }
		inline Property &operator=(const T&v) { set(v); return *this; }
		inline Property &operator=(T&&v) { set(std::move(v)); return *this; }

	private:
		Property<T> &m_value;
		callback_t m_callback;
	};

	template <typename T>
	class ReadOnlyProperty
	{
	public:
		constexpr ReadOnlyProperty(const Property<T> &p) noexcept : m_property{ p } {}
		constexpr inline const T &get() const noexcept { return m_property.get(); }
		constexpr inline const T &operator()() const noexcept { return m_property(); }

	private:
		const Property<T> &m_property;
	};
}

#endif
