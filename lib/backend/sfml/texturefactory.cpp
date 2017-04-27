#include "texturefactory.hpp"
#include <SFML/Graphics/Texture.hpp>


namespace lib
{
	namespace backend
	{
		sptr<ITexture> TextureFactory::loadTextureFromDisk(const str & file)
		{
			return sptr<ITexture>();
		}

		sptr<ITexture> TextureFactory::getITexture(const sf::Texture & texture)
		{
			return sptr<ITexture>();
		}
	}
}
