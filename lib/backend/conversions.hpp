#ifndef LIB_BACKEND_CONVERSIONS_INCLUDE_HPP__
#define LIB_BACKEND_CONVERSIONS_INCLUDE_HPP__

#pragma once

namespace sf
{
	class Texture;
}

namespace lib
{
	namespace draw
	{
		class Texture;
	}
	namespace backend
	{
		const sf::Texture *convert(const draw::Texture*texture);
	}
}

#endif
