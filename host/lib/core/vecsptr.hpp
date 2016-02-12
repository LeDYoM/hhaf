#ifndef __LIB_VECSPTR_HPP__
#define __LIB_VECSPTR_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include "log.hpp"

namespace lib
{
	template <typename T> using VecSPtr = std::vector<sptr<T>>;

	template <typename T, class Y>
	bool removeFromspVector(lib::sptr<T> element, std::vector<lib::sptr<Y>> &container)
	{
		auto i = container.begin();

		while (i != container.end())
		{
			if ((*i).get() == element.get())
			{
				i = container.erase(i);
				LOG_DEBUG("Element was found. Number of left references: " << element.use_count());
				return true;
			}
			else
			{
				++i;
			}
		}

		LOG_ERROR("Element " << element << " not found in list");
		return false;
	}
}

#endif
