#ifndef __LIB_TYPES_HPP__
#define __LIB_TYPES_HPP__

#include <cstdint>
#include <memory>
#include <lib/core/compileconfig.hpp>

#include <SFML/System/Vector2.hpp>

namespace lib
{
	template <typename T>
	using sptr = std::shared_ptr<T>;

	template <typename T>
	using uptr = std::unique_ptr<T>;

	template <typename T>
	using wptr = std::weak_ptr<T>;

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

	using vector2du32 = sf::Vector2u;
	using vector2ds32 = sf::Vector2i;
	using vector2df = sf::Vector2f;
	using vector2du8 = sf::Vector2<u8>;
	using vector2ds8 = sf::Vector2<s8>;

	struct Rect
	{
		vector2du32 begin;
		vector2du32 size;

		bool inBounds(const vector2ds32&point)
		{
			if (point.x < 0 || point.y < 0 
				|| point.x < (s32)begin.x || point.y < (s32)begin.y || point.x > (s32)(begin.x + size.x) || point.y > (s32)(begin.y + size.y))
				return false;

			return true;
		}
	};



}


#endif
