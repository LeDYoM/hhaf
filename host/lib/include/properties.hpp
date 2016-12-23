#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "compconfig.hpp"
#include <functional>

namespace lib
{
	template <typename T>
	class IReadOnlyProperty
	{
		virtual const T &get() const noexcept = 0;
	};

	template <typename T>
	class IProperty : public IReadOnlyProperty<T>
	{
		virtual void set(const T&v) noexcept = 0;
	};

	template <typename T>
	class Property;

	template <typename T>
	class ReadOnlyProperty : public IReadOnlyProperty<T>
	{
	public:
		ReadOnlyProperty(T&iv) noexcept : m_value{ iv } {}

		const T &get() const noexcept override { return m_value; }
	private:
		T& m_value;
	};

	template <typename T>
	class Property : public IProperty<T>
	{
	public:
		Property(T&iv) noexcept : m_value{ iv } {}

		const T &get() const noexcept override { return m_value; }
		void set(const T&v) noexcept override { m_value = v; }
	private:
		T& m_value;

	};

	template <typename T>
	class NotifableProperty : public IProperty<T>
	{
	public:
		NotifableProperty(T& iv, std::function<void()> callback) noexcept 
			: m_value{ iv }, m_callback{ callback } {}

		const T &get() const noexcept override { return m_value; }
		void set(const T&v) noexcept override { m_value = v; if (m_callback) m_callback(); }
	private:
		T& m_value;
		std::function<void()> m_callback;
	};
}

#endif
