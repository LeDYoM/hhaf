#ifndef LIB_DRAW_TEXTURE_INCLUDE_HPP__
#define LIB_DRAW_TEXTURE_INCLUDE_HPP__

#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace draw
	{
		class Texture : public sf::Texture
		{
		public:
			using sf::Texture::Texture;

			virtual ~Texture() {}
		};
	}
}

#endif
