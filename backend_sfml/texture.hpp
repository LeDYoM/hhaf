#pragma once

#ifndef LIB_BACKEND_SFML_TEXTURE_INCLUDE_HPP__
#define LIB_BACKEND_SFML_TEXTURE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/include/backend/itexture.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace lib::backend::sfmlb
{
	class Texture : public ITexture
	{
	public:
		Texture(uptr<sf::Texture> &&texture);
		virtual ~Texture();

		virtual vector2du32 size() const override;

		const sf::Texture &backEndTexture() const { return *m_texturePrivate; }
	private:
		uptr<sf::Texture> m_texturePrivate;
	};
}

#endif
