#ifndef LIB_DRAW_TEXTURE_INCLUDE_HPP__
#define LIB_DRAW_TEXTURE_INCLUDE_HPP__

#include <SFML/Graphics/Texture.hpp>
#include <lib/draw/hasname.hpp>

namespace lib
{
	namespace draw
	{
		class Texture : public sf::Texture, public core::HasName
		{
		public:
			Texture(const std::string name) : core::HasName(name) {}
			Texture(const sf::Texture &texture) : core::HasName("internal"), sf::Texture(texture) {}
		};
	}
}

#endif
