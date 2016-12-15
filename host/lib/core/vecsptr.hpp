#ifndef __LIB_VECSPTR_HPP__
#define __LIB_VECSPTR_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include "log.hpp"

namespace lib
{
	template <typename T> using VecSPtr = std::vector<sptr<T>>;

	template <typename T, class Y>
	bool removeFromspVector(sptr<T> element, std::vector<sptr<Y>> &container)
	{
		std::remove(container.begin(), container.end(),element);
		/*
		auto i = container.begin();

		while (i != container.end()) {
			if ((*i).get() == element.get()) {
				i = container.erase(i);
				logDebug("Element was found. Number of left references: ", element.use_count());
				return true;
			}
			else {
				++i;
			}
		}
		*/

		logError("Element ", element , " not found in list");
		return false;
	}
}

#endif
