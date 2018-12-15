#pragma once

#ifndef LIB_VSP_HPP__
#define LIB_VSP_HPP__

#include "types.hpp"
#include <algorithm>

namespace lib
{
    template <typename T>
    class deferred_loop_vector
    {
    public:
        using inner_content_t = wptr<T>;
        using exposed_content_t = sptr<T>;
        using container_t = vector<inner_content_t>;

        container_t nodes;
        bool m_looping{ false };
        
        void deferred_remove()
        {
            if (!nodes.empty() && !m_nodesToDelete.empty()) {
                container_t result;
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
        vector<sptr<T>> m_nodesToDelete;
    };
}

#endif
