#pragma once

#ifndef LIB_RESOURCEFACTORY_INCLUDE_HPP__
#define LIB_RESOURCEFACTORY_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include "resource.hpp"
#include <map>

namespace lib
{
	namespace core
	{
		class ResourceFactory
		{
		public:
			ResourceFactory(str resourceTypeName) : m_resourceTypeName{ std::move(resourceTypeName) } {}
			~ResourceFactory();

			template <typename T>
			sptr<Resource<T>> getResource(const str &rid) const
			{
				return {};
			}

			enum class ResourceLoadError : u16
			{
				Ok,
				FileNotFound,
				IdAlreadyExists,
				UnknownError
			};
			ResourceLoadError addResourceToLoad(const str &id, const str &fileName);
		private:
			virtual bool loadResource(const str &fileName, const vector<char>&data) = 0;
			str m_resourceTypeName;
			std::map<str, sptr<IResource>> m_resourceMap;
		};
	}
}

#endif
