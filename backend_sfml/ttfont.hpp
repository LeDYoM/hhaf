#ifndef LIB_BACKEND_SFML_TTFONT_INCLUDE_HPP__
#define LIB_BACKEND_SFML_TTFONT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/include/backend/ittfont.hpp>
#include <lib/include/backend/itexture.hpp>

#include <SFML/Graphics/Font.hpp>

#include <map>

namespace lib::backend::sfmlb
{
    class TextureTTFont;
	class TTFont : public ITTFont
	{
	public:
		TTFont(uptr<sf::Font> f);
        ~TTFont() override;

		virtual ITTGlyph getGlyph(u32 codePoint, u32 characterSize) const override;
		virtual f32 getLineSpacing(u32 characterSize) const override;
		virtual f32 getKerning(u32 first, u32 second, u32 characterSize) const override;
		virtual ITexture *getTexture(u32 characterSize) override;
	private:
		uptr<sf::Font> m_font;
		std::map<u32,TextureTTFont*> m_fontTexturesCache;
	};
}

#endif
