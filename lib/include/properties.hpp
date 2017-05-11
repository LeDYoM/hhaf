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
		constexpr const T&operator()() const { return get(); }
	};

	template <typename T>
	class IPropertyWrite
	{
	public:
		virtual void set(T v) = 0;
		constexpr void operator=(T v) { set(std::move(v)); }
	};

	template <typename T>
	class IProperty : public IPropertyRead<T>, public IPropertyWrite<T> {
	public:
		using IPropertyWrite::operator=;
	};

	template <typename T>
	class VirtualPropertyRead : public IPropertyRead<T>
	{
	public:
		using getter_t = std::function<const T&()>;
		constexpr VirtualPropertyRead(getter_t getterp = {}) : getter{ std::move(getterp) } {}
		constexpr inline void setGetter(getter_t getterp) { getter = std::move(getterp); }
		virtual const T&get() const noexcept override { return getter(); }
	protected:
		getter_t getter;
	};

	template <typename T>
	class VirtualPropertyWrite : public IPropertyWrite<T>
	{
	public:
		using setter_t = std::function<void(T)>;
		constexpr VirtualPropertyWrite(setter_t setterp = {}) : setter{ std::move(setterp) } {}
		constexpr void setSetter(setter_t setterp) { setter = std::move(setterp); }
		virtual void set(T v) override { setter(std::move(v)); }
		using IPropertyWrite::operator=;
	protected:
		setter_t setter;
	};

	template <typename T>
	class VirtualProperty : public VirtualPropertyRead<T>, public VirtualPropertyWrite<T>, public IProperty<T>
	{
	public:
		constexpr VirtualProperty(const getter_t getterp = {}, const setter_t &setterp = {}) : VirtualPropertyRead{ getterp }, VirtualPropertyWrite{ setterp } {}
		constexpr void setGettterSetter(getter_t getterp, setter_t setterp) { setGetter(std::move(getterp)); setSetter(std::move(setterp)); }
	};

	template <typename T>
	class Property : public IProperty<T>
	{
	public:
		using callback_t = std::function<void()>;
		using IProperty<T>::operator=;
		constexpr Property(callback_t c) : m_value{ }, m_callback{ std::move(c) } {}
		constexpr Property(T iv = {}, callback_t c = {}) : m_value{ std::move(iv) }, m_callback{ std::move(c) } {}

		constexpr void setCallback(callback_t c) { m_callback = std::move(c); }

		virtual const T &get() const noexcept override { return m_value; }
		virtual void set(T v) override { m_value = std::move(v); update(); }

		constexpr void update() { if (m_callback) m_callback(); }
	private:
		T m_value;
		callback_t m_callback;
	};

	template <typename T>
	class ForwardProperty : public IProperty<T>
	{
	public:
		constexpr ForwardProperty() {}
		constexpr ForwardProperty(IProperty<T> *const iv) : m_value{ iv } {}

		constexpr void setForwardProperty(IProperty<T> *const p) { m_value = p; }

		virtual const T &get() const noexcept override { return (*m_value).get(); }
		virtual void set(T v) override { (*m_value).set(std::move(v)); }
		using IProperty::operator=;
		inline IProperty<T> *const innerProperty() const { return m_value; }

	private:
		IProperty<T> *m_value{ nullptr };
	};

	class IPropertyOwner
	{
		virtual void onPropertySet() = 0;
	};

	template <typename T>
	class Property_ : public IProperty<T>
	{
	public:
		constexpr Property_(IPropertyOwner &propOwner, T iv = {}) : m_propertyOwner{ propOwner }, m_value{ std::move(iv) } {}

		virtual const T &get() const noexcept override { return m_value; }
		virtual void set(T v) override { m_value = v; update(); }
		virtual void operator=(const T&v) override { m_value = std::move(v); update(); }

		constexpr void update() { m_propertyOwner.onPropertySet(); }
	private:
		IPropertyOwner &m_propertyOwner;
		T m_value;
	};
}

#endif
