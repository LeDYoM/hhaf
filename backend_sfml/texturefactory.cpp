#include <mtypes/include/types.hpp>

#include "texturefactory.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace lib::backend::sfmlb
{
	ITexture *TextureFactory::loadFromFile(const str & file)
	{
		uptr<sf::Texture> texture(muptr<sf::Texture>());
		texture->loadFromFile(file.c_str());
		uptr<Texture> t{ muptr<Texture>(std::move(texture)) };
		m_textureCache.push_back(std::move(t));
		return (*(m_textureCache.end()-1)).get();
	}

	TextureFactory::~TextureFactory()
	{
		m_textureCache.clear();
		m_textureCache.shrink_to_fit();
	}
}
