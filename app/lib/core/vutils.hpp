#ifndef __LIB_VUTILS_HPP__
#define __LIB_VUTILS_HPP__

#include "log.hpp"
#include <lib/core/vutils.hpp>
#include <vector>

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

#endif
