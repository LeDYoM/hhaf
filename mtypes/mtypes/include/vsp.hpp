#pragma once

#ifndef LIB_VSP_HPP__
#define LIB_VSP_HPP__

#include "types.hpp"
#include <algorithm>

namespace lib
{
	template <typename T>
	class vsp_with_deferred_delete
	{
	public:
		vector_shared_pointers<T> nodes;

		void deferred_remove()
		{
			if (!nodes.empty() && !m_nodesToDelete.empty()) {
				vector_shared_pointers<T> result;
				result.reserve(nodes.size());
				std::for_each(nodes.cbegin(), nodes.cend(), [this, &result](const sptr<T>& containedElement) {
					if (std::find(m_nodesToDelete.cbegin(), m_nodesToDelete.cend(), containedElement) == m_nodesToDelete.cend()) {
						result.push_back(containedElement);
					}
				});
				std::swap(nodes, result);
				m_nodesToDelete.clear();
			}
		}

		bool has_pendingNodes_for_deletion() const { return !m_nodesToDelete.empty(); }
		vector_shared_pointers<T> m_nodesToDelete;
	};
}

#endif
