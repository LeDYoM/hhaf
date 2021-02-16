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
        TTFont(mtps::uptr<sf::Font> f, mtps::RawMemory raw_memory);
        ~TTFont() override;

        mtps::Rectf32 getBounds(const mtps::u32 codePoint, const mtps::u32 characterSize) const override;
        mtps::Rectf32 getTextureBounds(const mtps::u32 codePoint, const mtps::u32 characterSize) const override;
        mtps::f32 getAdvance(const mtps::u32 codePoint, const mtps::u32 characterSize) const override;
        mtps::f32 getLineSpacing(const mtps::u32 characterSize) const override;
        mtps::f32 getKerning(const mtps::u32 first, const mtps::u32 second, const mtps::u32 characterSize) const override;
        ITexture *getTexture(const mtps::u32 characterSize) override;
    private:
        mtps::uptr<sf::Font> m_font;
        mtps::RawMemory raw_memory_;
        std::map<mtps::u32, mtps::uptr<Texture>> m_fontTexturesCache;
    };
}

#endif
