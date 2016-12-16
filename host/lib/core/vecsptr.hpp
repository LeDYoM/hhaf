#ifndef __LIB_VECSPTR_HPP__
#define __LIB_VECSPTR_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include "log.hpp"

namespace lib
{
	template <typename T> using VecSPtr = std::vector<sptr<T>>;

	template <typename ContainerType, typename T>
	bool removeFromspVector(ContainerType &container, const sptr<T> &element)
	{
		auto iterator(std::find(std::begin(container), std::end(container), element));
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
