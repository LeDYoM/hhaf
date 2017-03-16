#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "compconfig.hpp"
#include <functional>

namespace lib
{
	template <typename T>
	class VirtualPropertyRead
	{
	public:
		using getter_t = std::function<const T&()>;
		constexpr VirtualPropertyRead(const getter_t &getterp = {}) : getter{ getterp } {}
		inline void setGetter(const getter_t &getterp) { getter = getterp; }
		constexpr const T&get() const noexcept { return getter(); }
		constexpr const T&operator()() const noexcept { return get(); }
	protected:
		getter_t getter;
	};

	template <typename T>
	class VirtualPropertyWrite
	{
	public:
		using setter_t = std::function<void(const T&)>;
		constexpr VirtualPropertyWrite(const setter_t &setterp = {}) : setter{ setterp } {}
		inline void setSetter(const setter_t &setterp) { setter = setterp; }
		inline void set(const T&v) { setter(v); }
		inline void set(T&&v) { setter(std::move(v)); }
		inline void operator=(const T&v) { set(v); }
		inline void operator=(T&&v) { set(std::move(v)); }
	protected:
		setter_t setter;
	};

	template <typename T>
	class VirtualProperty : public VirtualPropertyRead<T>, public VirtualPropertyWrite<T>
	{
	public:
		constexpr VirtualProperty(const getter_t &getterp = {}, const setter_t &setterp = {}) : VirtualPropertyRead{ getterp }, VirtualPropertyWrite{ setterp } {}
	};

	template <typename T>
	class Property
	{
	public:
		using callback_t = std::function<void()>;
		constexpr Property(T iv = {}, callback_t c = {}) noexcept : m_value{ std::move(iv) }, m_callback{ std::move(c) } {}
		Property(const Property&) = delete;
		Property& operator=(const Property&) = delete;

		constexpr const T &operator()() const { return m_value; }
		inline void setCallback(callback_t c) { m_callback = std::move(c); }
		constexpr const T &get() const { return m_value; }
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
		using callback_t = std::function<void()>;
		constexpr ForwardProperty() {}
		constexpr ForwardProperty(Property<T> *const iv) noexcept : m_value{ iv } {}
		ForwardProperty(const ForwardProperty&) = delete;
		ForwardProperty& operator=(const ForwardProperty&) = delete;

		constexpr const T &operator()() const noexcept { return (*m_value)(); }
		inline void setForwardProperty(Property<T> *const p) noexcept { m_value = p; }
		inline void setCallback(callback_t nc) noexcept { m_callback = nc; }
		constexpr const T &get() const { return (*m_value).get(); }
		inline void set(const T&v) { (*m_value) = v; update(); }
		inline void set(T&&v) { (*m_value) = std::move(v); update(); }
		inline ForwardProperty &operator=(const T&v) { set(v); return *this; }
		inline ForwardProperty &operator=(T&&v) { set(std::move(v)); return *this; }
		inline Property<T> *const innerProperty() const { return m_value; }
		inline void update() { if (m_callback) m_callback(); }

	private:
		Property<T> *m_value{ nullptr };
		callback_t m_callback;
	};
}

#endif
