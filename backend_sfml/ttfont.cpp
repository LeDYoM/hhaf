#include "ttfont.hpp"
#include "conversions.hpp"

using namespace htps;

namespace haf::backend::sfmlb
{
TTFont::TTFont(uptr<sf::Font> f, RawMemory raw_memory) :
    font_{std::move(f)}, raw_memory_{std::move(raw_memory)}
{}
TTFont::~TTFont() = default;

Rectf32 TTFont::getBounds(const u32 codePoint, const u32 characterSize) const
{
    return from_sf_type<f32>(
        font_->getGlyph(codePoint, characterSize, false).bounds);
}

Rectf32 TTFont::getTextureBounds(const u32 codePoint,
                                 const u32 characterSize) const
{
    return from_sf_type<s32>(
        font_->getGlyph(codePoint, characterSize, false).textureRect);
}

f32 TTFont::getAdvance(const u32 codePoint, const u32 characterSize) const
{
    return static_cast<f32>(
        font_->getGlyph(codePoint, characterSize, false).advance);
}

f32 TTFont::getLineSpacing(const u32 characterSize) const
{
    return font_->getLineSpacing(characterSize);
}

f32 TTFont::getKerning(const u32 first,
                       const u32 second,
                       const u32 characterSize) const
{
    return font_->getKerning(first, second, characterSize);
}

ITexture* TTFont::getTexture(const u32 characterSize)
{
    if (auto iterator(font_textures_cache_.find(characterSize));
        iterator != font_textures_cache_.end())
    {
        return iterator->second.get();
    }

    auto nTexture(muptr<Texture>(&font_->getTexture(characterSize), false));

    // What is needed here is to force the load of the font surface
    for (u32 i{0U}; i < 0xff; ++i)
    {
        getTextureBounds(i, characterSize);
    }

    auto* ret(nTexture.get());
    font_textures_cache_[characterSize] = std::move(nTexture);
    return ret;
}
}  // namespace haf::backend::sfmlb
