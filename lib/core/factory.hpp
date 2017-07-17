#pragma once

#ifndef LIB_FACTORY_INCLUDE_HPP__
#define LIB_FACTORY_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib
{
	template <typename T>
	class Factory
	{
	public:
		Factory();
		virtual ~Factory();

		T*create() {
			return new T;
		}

		sptr<T> createShared()
		{
			return 
		}
	};
}

#endif
