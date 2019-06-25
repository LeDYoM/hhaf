#pragma once

#ifndef LIB_BACKEND_SFML_TEXTURE_INCLUDE_HPP__
#define LIB_BACKEND_SFML_TEXTURE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <backend_dev/include/itexture.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace lib::backend::sfmlb
{
	class Texture : public ITexture
	{
	public:
		Texture(const sf::Texture* const texture, const bool owned);
		~Texture() override;

		virtual vector2du32 size() const override;

		const sf::Texture &backEndTexture() const { return *m_texturePrivate; }
	private:
		const sf::Texture* const m_texturePrivate;
		const bool owned_;
	};
}

#endif
