#ifndef __LIB_TYPES_HPP__
#define __LIB_TYPES_HPP__

#include <cstdint>
#include <memory>
#include "compileconfig.hpp"

#include <SFML/System/Vector2.hpp>

namespace lib
{
	template <typename T>
	using sptr = std::shared_ptr<T>;

	template <typename T>
	using uptr = std::unique_ptr<T>;

	template <typename T>
	using wptr = std::weak_ptr<T>;

	using u32 = uint32_t;
	using s32 = int_fast32_t;
	using u16 = uint16_t;
	using s16 = int_fast16_t;
	using u8 = uint8_t;
	using s8 = int_fast8_t;

	using vector2du32 = sf::Vector2u;
	using vector2ds32 = sf::Vector2i;
	using vector2df = sf::Vector2f;


}


#endif
