#include "texturefactory.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

namespace lib
{
	namespace backend
	{
		sptr<ITexture> TextureFactory::loadTextureFromDisk(const str & file)
		{
			sf::Texture texture;
			texture.loadFromFile(file);
			return msptr<Texture>(texture);
		}

		sptr<ITexture> TextureFactory::getITexture(const sf::Texture & texture)
		{
			return msptr<Texture>(texture);
		}
	}
}
