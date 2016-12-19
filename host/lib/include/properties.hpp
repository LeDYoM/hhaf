#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "compconfig.hpp"

namespace lib
{
	template <typename T>
	class ReadOnlyProperty
	{
	public:
		explicit constexpr ReadOnlyProperty() noexcept : m_value{} {}
		ReadOnlyProperty(const T&iv) noexcept : m_value{ iv } {}
		ReadOnlyProperty(T&&iv) noexcept : m_value{ std::move(iv) } {}

		const T &get() const noexcept { return m_value; }
	private:
		T m_value;
		friend class Property<T>;
	};

	template <typename T>
	class Property : public ReadOnlyProperty
	{
	public:
		using ReadOnlyProperty::ReadOnlyProperty;

		void set(const T&v) noexcept { m_value = v; }
	};

	template <typename T>
	class NotifableProperty
	{
	public:
		NotifableProperty(const T&iv, std::function<void>(const <typename T> &) callback) noexcept 
			: m_value{ iv }, m_callback{ callback } {}
		NotifableProperty(T&&iv) noexcept : m_value{ std::move(iv) } {}

		const T &get() const noexcept { return m_value; }
		void set(const T&v) noexcept { m_value = v; if (m_callback) m_callback(m_value); }
	private:
		T m_value;
		std::function<void(const typename T&)> m_callback;
	};
}

#endif
