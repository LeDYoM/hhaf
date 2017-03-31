#ifndef __LIB_TYPES_HPP__
#define __LIB_TYPES_HPP__

#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>

namespace lib
{
	template <typename T>
	using sptr = std::shared_ptr<T>;

	template <typename T>
	using uptr = std::unique_ptr<T>;

	template <typename T, typename... Args>
	constexpr sptr<T> msptr(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

	template <typename T, typename... Args>
	constexpr uptr<T> muptr(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }

	template <typename T>
	using wptr = std::weak_ptr<T>;

	template <typename T> 
	using vector_shared_pointers = std::vector<sptr<T>>;
	
	template <typename T> 
	using list_shared_pointers = std::vector<sptr<T>>;

	template <typename T>
	using vector_unique_pointers = std::vector<uptr<T>>;

	template <typename T>
	bool remove1_vsp(vector_shared_pointers<T> &container, const sptr<T> &element)
	{
		auto iterator(container.cbegin(), container.cend(), element);
		if (iterator != container.cend()) {
			container.erase(iterator);
			return true;
		}
		else {
			return false;
		}
	}

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

	using u64 = uint64_t;
	using s64 = int64_t;
	using u32 = uint32_t;
	using s32 = int32_t;
	using u16 = uint16_t;
	using s16 = int16_t;
	using u8 = uint8_t;
	using s8 = int8_t;
	using f32 = float;
	using f64 = double;
	using str_const = std::string;
	using write_stream = std::ostream;

	using string_vector = std::vector<str_const>;
}

#endif
