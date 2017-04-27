#include "texturefactory.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

namespace lib
{
	namespace backend
	{
		sptr<ITexture> TextureFactory::loadTextureFromDisk(const str & file)
		{
			return sptr<Texture>();
		}

		sptr<ITexture> TextureFactory::getITexture(const sf::Texture & texture)
		{
			return sptr<ITexture>();
		}
	}
}
