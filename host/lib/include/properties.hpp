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
		constexpr Property(T iv = T{}, callback_t &&c = nullptr) noexcept : m_value{std::move(iv) }, m_callback{ std::move(c) } {}
		constexpr Property(T &&iv, callback_t &&c = nullptr) noexcept : m_value{ std::move(iv) }, , m_callback{ std::move(c) } {}

		void setCallback(callback_t&&c) noexcept { m_callback = std::move(c); }
		const T &get() const noexcept { return m_value; }
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
		ReadOnlyProperty(const Property<T> &p) : m_property{ p } {}
		inline const T &get() const noexcept { return m_property.get(); }

	private:
		Property<T> &m_property;
	};
}

#endif
