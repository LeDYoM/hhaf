#ifndef __LIB_TYPES_HPP__
#define __LIB_TYPES_HPP__

#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <lib/core/compileconfig.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	template <typename T>
	using sptr = std::shared_ptr<T>;

	template <typename T>
	using uptr = std::unique_ptr<T>;

	template <typename T, typename... Args>
	constexpr inline sptr<T> msptr(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

	template <typename T, typename... Args>
	constexpr inline uptr<T> muptr(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }

	template <typename T>
	using wptr = std::weak_ptr<T>;

	template <typename T> 
	using vector_shared_pointers = std::vector<sptr<T>>;
	
	template <typename T> 
	using list_shared_pointers = std::vector<sptr<T>>;

	template <typename ContainerType, typename T>
	bool removespFrom(ContainerType &container, const sptr<T> &element)
	{
		auto iterator(std::find(std::cbegin(container), std::cend(container), element));
		if (iterator != container.cend()) {
			container.erase(iterator);
			return true;
		}
		else {
			logError("Element ", element, " not found in list");
			return false;
		}
	}

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
}

#endif
