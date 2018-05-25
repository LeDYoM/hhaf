#include "texturettfont.hpp"
#include <lib/include/backend/itexture.hpp>

namespace lib::backend::sfmlb
{
	TextureTTFont::TextureTTFont(const sf::Texture &texture) : m_texturePrivate{ std::move(texture) } {}

    TextureTTFont::~TextureTTFont() {}

	vector2du32 TextureTTFont::size() const
	{
		return{ static_cast<u32>(m_texturePrivate.getSize().x), static_cast<u32>(m_texturePrivate.getSize().y) };
	}
}
