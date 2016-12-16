#ifndef __LIB_VECSPTR_HPP__
#define __LIB_VECSPTR_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include "log.hpp"

namespace lib
{
	template <typename T> using VecSPtr = std::vector<sptr<T>>;

	template <typename T, class Y>
	bool removeFromspVector(const sptr<T> &element, std::vector<sptr<Y>> &container)
	{
		auto iterator(std::find(container.cbegin(), container.cend(), element));
		if (iterator != container.cend()) {
			container.erase(iterator);
			return true;
		}
		else {
			logError("Element ", element, " not found in list");
			return false;
		}
	}
}

#endif
