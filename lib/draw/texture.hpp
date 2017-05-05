#ifndef LIB_DRAW_TEXTURE_INCLUDE_HPP__
#define LIB_DRAW_TEXTURE_INCLUDE_HPP__

#include <lib/draw/hasname.hpp>
#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

namespace sf
{
	class Texture;
}

namespace lib
{
	namespace backend
	{
		class ITexture;
	}
	namespace draw
	{
		class Texture final : public core::HasName
		{
		public:
			Texture(str name);
			Texture(const sf::Texture &texture);
			Texture(sptr<backend::ITexture> texture);
			virtual ~Texture();

			bool loadFromFile(const str& filename);
			vector2du32 size() const;

			const sptr<backend::ITexture> backEndTexture() const { return m_texturePrivate; }
		private:
			sptr<backend::ITexture> m_texturePrivate;
		};
	}
}

#endif
