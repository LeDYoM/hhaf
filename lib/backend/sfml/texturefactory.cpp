#include "texturefactory.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			sptr<ITexture> TextureFactory::loadFromFile(const str & file)
			{
				uptr<sf::Texture> texture(muptr<sf::Texture>());
				texture->loadFromFile(file);
				return msptr<Texture>(std::move(texture));
			}
		}
	}
}
