#include "texturefactory.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			ITexture *TextureFactory::loadFromFile(const str & file)
			{
				uptr<sf::Texture> texture(muptr<sf::Texture>());
				texture->loadFromFile(file);
				Texture *t{ new Texture(std::move(texture)) };
				m_textureCache.push_back(t);
				return t;
			}

			TextureFactory::~TextureFactory()
			{
				for (Texture *texture : m_textureCache) {
					delete texture;
				}

				m_textureCache.clear();
			}
		}
	}
}
