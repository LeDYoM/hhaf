#pragma once

#ifndef LIB_BACKEND_SFML_TEXTURETTFONT_INCLUDE_HPP
#define LIB_BACKEND_SFML_TEXTURETTFONT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/include/backend/itexture.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace lib::backend::sfmlb
{
    /// Class to store a non-owning const reference to a sf::Texture.
    /// TThis class is usful when the user did not create the 
    /// associated sf::Texture but can only have a const reference to it.
    class TextureTTFont : public ITexture
	{
	public:
        /// Constructs an instance from a non owning const reference.
        /// @param texture The non-owning const reference
		TextureTTFont(const sf::Texture &texture) 
            : m_texturePrivate{ texture } {}

        /// Empty destructor
        ~TextureTTFont() override {}

        /// Returns the size of the texture in pixels
        /// @return A vector2du containing the size
        vector2du32 size() const override
        {
            return{ static_cast<u32>(m_texturePrivate.getSize().x), static_cast<u32>(m_texturePrivate.getSize().y) };
        }

        /// Method to retrieve the internal texture.
        /// @returns The internal texture.
		inline const sf::Texture &backEndTexture() const { return m_texturePrivate; }
	private:
		const sf::Texture &m_texturePrivate;
	};
}

#endif
