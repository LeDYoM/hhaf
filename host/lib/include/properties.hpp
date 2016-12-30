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
		using callback_t = std::function<void(const T &newValue)>;
		constexpr Property(T iv, callback_t c) noexcept : m_value{ std::move(iv) }, m_callback{ std::move(c) } {}

		Property(const Property&) = delete;
		Property& operator=(const Property&) = delete;
		Property(Property&&) = delete;
		Property& operator=(Property&&) = delete;

		void setCallback(callback_t&&c) noexcept { m_callback = std::move(c); }
		constexpr const T &get() const noexcept { return m_value; }
		void set(const T&v) { m_value = v; if (m_callback) m_callback(m_value); }
		void set(T&&v) { m_value = std::move(v); if (m_callback) m_callback(m_value); }
	private:
		T m_value;
		callback_t m_callback;
	};

	template <typename T>
	class ReadOnlyProperty
	{
	public:
		constexpr ReadOnlyProperty(const Property<T> &p) noexcept : m_property{ p } {}
		constexpr inline const T &get() const noexcept { return m_property.get(); }

	private:
		const Property<T> &m_property;
	};
}

#endif
