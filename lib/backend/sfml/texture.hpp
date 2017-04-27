#ifndef LIB_BACKEND_SFML_TEXTURE_INCLUDE_HPP__
#define LIB_BACKEND_SFML_TEXTURE_INCLUDE_HPP__

#include <lib/draw/hasname.hpp>
#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/backend/itexture.hpp>

namespace sf
{
	class Texture;
}

namespace lib
{
	namespace backend
	{
		class Texture : public ITexture
		{
		public:
			Texture(str name, const sf::Texture &texture);
			virtual ~Texture();

			virtual vector2du32 size() const override;

			const sf::Texture &backEndTexture() const { return m_texturePrivate; }
		private:
			sf::Texture m_texturePrivate;
		};
	}
}

#endif
