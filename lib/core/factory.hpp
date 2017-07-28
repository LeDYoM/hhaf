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
		constexpr void registerSingletonType() noexcept
		{
			m_registeredTypes.emplace(typeid(T), nullptr);
		}

		template <typename T>
		constexpr sptr<T> registerSingletonInstance(sptr<T> pElement) noexcept
		{
			m_registeredTypes.emplace(typeid(T), pElement);
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
			return typeRegistered<T>() ? getSingleton<T>() : registerSingletonInstance<T>(msptr<T>());
		}

		template <typename T>
		constexpr sptr<interface_type> getSingletonInterface()
		{
			auto iterator(m_registeredTypes.find(typeid(T)));
			if (iterator != m_registeredTypes.end()) {
				// If the instance of the type is still not created
				if (!(*iterator).second) {
					(*iterator).second = msptr<T>();
				}
				return (*iterator).second;
			}
			return nullptr;
		}

		template <typename T>
		constexpr sptr<T> getSingleton()
		{
			return std::dynamic_pointer_cast<T>(getSingletonInterface<T>());
		}

	private:
		std::map<std::type_index,sptr<interface_type>> m_registeredTypes;
	};

}

#endif
