#ifndef LIB_BACKEND_SFML_TTFONT_INCLUDE_HPP__
#define LIB_BACKEND_SFML_TTFONT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/backend/ittfont.hpp>
#include <lib/backend/itexture.hpp>

#include <SFML/Graphics/Font.hpp>

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			class TTFont : public ITTFont
			{
			public:
				TTFont(const sf::Font &f);
				virtual ~TTFont();

				virtual const ITTGlyph getGlyph(u32 codePoint, u32 characterSize, bool bold, f32 outlineThickness) const override;
				virtual f32 getLineSpacing(u32 characterSize) const override;
				virtual f32 getKerning(u32 first, u32 second, u32 characterSize) const override;
				virtual ITexture *getTexture(u32 characterSize) const override;
			private:
				sf::Font m_font;
			};
		}
	}
}
#endif
