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
		constexpr Property(T iv) noexcept : m_value{ std::move(iv) } {}

		Property(const Property&) = delete;
		Property& operator=(const Property&) = delete;

		constexpr const T &operator()() const noexcept { return m_value; }
		constexpr const T &get() const noexcept { return m_value; }
		inline void set(const T&v) { m_value = v; }
		inline void set(T&&v) { m_value = std::move(v); }
		Property &operator=(const T&v) { set(v); return *this; }
		Property &operator=(T&&v) { set(std::move(v)); return *this; }
	private:
		T m_value;
	};

	template <typename T>
	class TriggerProperty
	{
	public:
		using callback_t = std::function<void(const T &newValue)>;
		constexpr TriggerProperty(T iv, callback_t c) noexcept : m_value{ std::move(iv) }, m_callback{ std::move(c) } {}
		constexpr TriggerProperty(const Property<T> &pr, callback_t c) noexcept : m_value{ std::move(pr) }, m_callback{ std::move(c) } {}

		TriggerProperty(const TriggerProperty&) = delete;
		TriggerProperty& operator=(const TriggerProperty&) = delete;
		TriggerProperty(TriggerProperty&&) = delete;
		TriggerProperty& operator=(TriggerProperty&&) = delete;

		constexpr const T &operator()() const noexcept { return m_value(); }
		void setCallback(callback_t c) noexcept { m_callback = std::move(c); }
		constexpr const T &get() const noexcept { return m_value.get(); }
		inline void set(const T&v) { m_value.set(v); if (m_callback) m_callback(m_value()); }
		inline void set(T&&v) { m_value.set(std::move(v)); if (m_callback) m_callback(m_value()); }
		TriggerProperty &operator=(const T&v) { set(v); return *this; }
		TriggerProperty &operator=(T&&v) { set(std::move(v)); return *this; }

		operator const Property<T>&() const { return m_value; }

	private:
		Property<T> m_value;
		callback_t m_callback;
	};

	template <typename T>
	class ReadOnlyProperty
	{
	public:
		constexpr ReadOnlyProperty(const Property<T> &p) noexcept : m_property{ p } {}
		constexpr inline const T &get() const noexcept { return m_property.get(); }
		constexpr const T &operator()() const noexcept { return m_property.get(); }

	private:
		const Property<T> &m_property;
	};
}

#endif
