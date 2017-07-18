#pragma once

#ifndef LIB_FACTORY_INCLUDE_HPP__
#define LIB_FACTORY_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <typeinfo>
#include <typeindex>
#include <map>
#include <memory>

namespace lib
{
	template <typename interface_type>
	class FactoryOfSingletons
	{
	public:

		template <typename T>
		constexpr sptr<T> registerSingleton(sptr<T> pElement) noexcept
		{
			m_registeredTypes[typeid(T)] = pElement;
			return pElement;
		}

		template <typename T>
		constexpr bool typeRegistered()
		{
			return m_registeredTypes.find(typeid(T)) != m_registeredTypes.end();
		}

		template <typename T>
		constexpr sptr<T> registerAndCreateSingleton()
		{
			return typeRegistered<T>() ? getSingleton<T>() : registerSingleton<T>(msptr<T>());
		}

		template <typename T>
		sptr<interface_type> getSingletonInterface()
		{
			auto iterator(m_registeredTypes.find(typeid(T)));
			return iterator != m_registeredTypes.end() ? *iterator : nullptr;
		}

		template <typename T>
		sptr<T> getSingleton()
		{
			auto iterator(m_registeredTypes.find(typeid(T)));
			return (iterator != m_registeredTypes.end()) ? std::dynamic_pointer_cast<T>((*iterator).second) : nullptr;
		}

	private:
		std::map<std::type_index,sptr<interface_type>> m_registeredTypes;
	};

}

#endif
