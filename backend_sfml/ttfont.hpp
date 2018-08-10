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

		virtual ITTGlyph getGlyph(const u32 codePoint, const u32 characterSize) const override;
		virtual f32 getLineSpacing(const u32 characterSize) const override;
		virtual f32 getKerning(const u32 first, const u32 second, const u32 characterSize) const override;
		virtual ITexture *getTexture(const u32 characterSize) override;
	private:
		uptr<sf::Font> m_font;
		std::map<u32, uptr<TextureTTFont>> m_fontTexturesCache;
	};
}

#endif
