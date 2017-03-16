#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "compconfig.hpp"
#include <functional>

namespace lib
{
	template <typename T>
	class IPropertyRead
	{
	public:
		virtual const T&get() const noexcept = 0;
		virtual const T&operator()() const noexcept = 0;
	};

	template <typename T>
	class IPropertyWrite
	{
	public:
		virtual void set(const T&v) = 0;
		virtual void set(T&&v) = 0;
		virtual void operator=(const T&v) = 0;
		virtual void operator=(T&&v) = 0;
	};

	template <typename T>
	class IProperty : public IPropertyRead<T>, public IPropertyWrite<T> {};

	template <typename T>
	class VirtualPropertyRead : public IPropertyRead<T>
	{
	public:
		using getter_t = std::function<const T&()>;
		constexpr VirtualPropertyRead(const getter_t &getterp = {}) : getter{ getterp } {}
		inline void setGetter(const getter_t &getterp) { getter = getterp; }
		virtual const T&get() const noexcept override { return getter(); }
		virtual const T&operator()() const noexcept override { return get(); }
	protected:
		getter_t getter;
	};

	template <typename T>
	class VirtualPropertyWrite : public IPropertyWrite<T>
	{
	public:
		using setter_t = std::function<void(const T&)>;
		constexpr VirtualPropertyWrite(const setter_t &setterp = {}) : setter{ setterp } {}
		inline void setSetter(const setter_t &setterp) { setter = setterp; }
		virtual void set(const T&v) override { setter(v); }
		virtual void set(T&&v) override { setter(std::move(v)); }
		virtual void operator=(const T&v) override { set(v); }
		virtual void operator=(T&&v) override { set(std::move(v)); }
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
	class Property : public IProperty<T>
	{
	public:
		using callback_t = std::function<void()>;
		constexpr Property(T iv = {}, callback_t c = {}) noexcept : m_value{ std::move(iv) }, m_callback{ std::move(c) } {}

		inline void setCallback(callback_t c) { m_callback = std::move(c); }

		virtual const T &operator()() const noexcept override { return m_value; }
		virtual const T &get() const noexcept override { return m_value; }
		virtual void set(const T&v) override { m_value = v; update(); }
		virtual void set(T&&v) override { m_value = std::move(v); update(); }
		virtual void operator=(const T&v) override { m_value = std::move(v); update(); }
		virtual void operator=(T&&v) override { m_value = std::move(v); update(); }

		void update() { if (m_callback) m_callback(); }
	private:
		T m_value;
		callback_t m_callback;
	};

	template <typename T>
	class ForwardProperty : public IProperty<T>
	{
	public:
		using callback_t = std::function<void()>;
		constexpr ForwardProperty() {}
		constexpr ForwardProperty(Property<T> *const iv) noexcept : m_value{ iv } {}

		inline void setForwardProperty(Property<T> *const p) noexcept { m_value = p; }
		inline void setCallback(callback_t nc) noexcept { m_callback = nc; }

		virtual const T &operator()() const noexcept override { return (*m_value)(); }
		virtual const T &get() const noexcept override { return (*m_value).get(); }
		virtual void set(const T&v) override { (*m_value) = v; update(); }
		virtual void set(T&&v) override { (*m_value) = std::move(v); update(); }
		virtual void operator=(const T&v) override { set(v); }
		virtual void operator=(T&&v) override { set(std::move(v)); }
		inline Property<T> *const innerProperty() const { return m_value; }
		inline void update() { if (m_callback) m_callback(); }

	private:
		Property<T> *m_value{ nullptr };
		callback_t m_callback;
	};
}

#endif
