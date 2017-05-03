#ifndef LIB_DRAW_TTFONT_INCLUDE_HPP__
#define LIB_DRAW_TTFONT_INCLUDE_HPP__

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <lib/draw/hasname.hpp>

namespace lib
{
	namespace draw
	{
		class TTFont final : public core::HasName
		{
		public:
			TTFont(str name);
			virtual ~TTFont();

			bool loadFromFile(const std::string& filename);
			const sf::Glyph& getGlyph(u32 codePoint, u32 characterSize, bool bold, float outlineThickness = 0) const;
			f32 getLineSpacing(u32 characterSize) const;
			f32 getKerning(u32 first, u32 second, u32 characterSize) const;
			const sf::Texture& getTexture(u32 characterSize) const;

		private:
			sptr<sf::Font> m_font;
		};
	}
}

#endif
