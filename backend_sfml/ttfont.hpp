#ifndef HAF_BACKEND_SFML_TTFONT_INCLUDE_HPP__
#define HAF_BACKEND_SFML_TTFONT_INCLUDE_HPP__

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/rawmemory.hpp>
#include <backend_dev/include/ittfont.hpp>
#include <backend_dev/include/itexture.hpp>

#include <SFML/Graphics/Font.hpp>

#include <map>

namespace haf::backend::sfmlb
{
    class Texture;
    class TTFont : public ITTFont
    {
    public:
        TTFont(htps::uptr<sf::Font> f, htps::RawMemory raw_memory);
        ~TTFont() override;

        htps::Rectf32 getBounds(const htps::u32 codePoint, const htps::u32 characterSize) const override;
        htps::Rectf32 getTextureBounds(const htps::u32 codePoint, const htps::u32 characterSize) const override;
        htps::f32 getAdvance(const htps::u32 codePoint, const htps::u32 characterSize) const override;
        htps::f32 getLineSpacing(const htps::u32 characterSize) const override;
        htps::f32 getKerning(const htps::u32 first, const htps::u32 second, const htps::u32 characterSize) const override;
        ITexture *getTexture(const htps::u32 characterSize) override;
    private:
        htps::uptr<sf::Font> m_font;
        htps::RawMemory raw_memory_;
        std::map<htps::u32, htps::uptr<Texture>> m_fontTexturesCache;
    };
}

#endif
