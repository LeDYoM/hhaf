#ifndef LIB_BACKEND_SFML_TTFONT_INCLUDE_HPP__
#define LIB_BACKEND_SFML_TTFONT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <backend_dev/include/ittfont.hpp>
#include <backend_dev/include/itexture.hpp>

#include <SFML/Graphics/Font.hpp>

#include <map>

namespace lib::backend::sfmlb
{
    class Texture;
	class TTFont : public ITTFont
	{
	public:
		TTFont(uptr<sf::Font> f);
        ~TTFont() override;

		Rectf32 getBounds(const u32 codePoint, const u32 characterSize) const override;
		Rectf32 getTextureBounds(const u32 codePoint, const u32 characterSize) const override;
		f32 getAdvance(const u32 codePoint, const u32 characterSize) const override;
		f32 getLineSpacing(const u32 characterSize) const override;
		f32 getKerning(const u32 first, const u32 second, const u32 characterSize) const override;
		ITexture *getTexture(const u32 characterSize) override;
	private:
		uptr<sf::Font> m_font;
		std::map<u32, uptr<Texture>> m_fontTexturesCache;
	};
}

#endif
