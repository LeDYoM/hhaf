#include "sfml_ttfont.hpp"
#include "conversions.hpp"
#include <SFML/Graphics/Font.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLTTFont::SFMLTTFont(uptr<sf::Font> font,
                       RawMemory raw_memory,
                       IResourceManager* iresource_manager) :
    font_{htps::move(font)},
    raw_memory_{htps::move(raw_memory)},
    iresource_manager_{iresource_manager}
{}

SFMLTTFont::~SFMLTTFont() = default;

Rectf32 SFMLTTFont::getBounds(const u32 codePoint,
                              const u32 characterSize) const
{
    return from_sf_type<f32>(
        font_->getGlyph(codePoint, characterSize, false).bounds);
}

Rectf32 SFMLTTFont::getTextureBounds(const u32 codePoint,
                                     const u32 characterSize) const
{
    return from_sf_type<s32>(
        font_->getGlyph(codePoint, characterSize, false).textureRect);
}

f32 SFMLTTFont::getAdvance(const u32 codePoint, const u32 characterSize) const
{
    return static_cast<f32>(
        font_->getGlyph(codePoint, characterSize, false).advance);
}

f32 SFMLTTFont::getLineSpacing(const u32 characterSize) const
{
    return font_->getLineSpacing(characterSize);
}

f32 SFMLTTFont::getKerning(const u32 first,
                           const u32 second,
                           const u32 characterSize) const
{
    return font_->getKerning(first, second, characterSize);
}

str SFMLTTFont::getTexture(const u32 characterSize, char const /*character*/)
{
    if (auto iterator{textures_ids_cache_.find(characterSize)};
        iterator != textures_ids_cache_.end())
    {
        return iterator->second;
    }
    else
    {
        auto* new_texture{
            new SFMLTexture{&font_->getTexture(characterSize), true}};

        // That is needed here is to force the load of the font surface
        // TODO: Check if it is still needed
        for (u32 i{0U}; i < 0xFF; ++i)
        {
            (void)(getTextureBounds(i, characterSize));
        }

        str returned_id{iresource_manager_->setExternalTexture(new_texture)};
        textures_ids_cache_[characterSize] = returned_id;
//        return nTexture.get();
    }

    return "";
}
}  // namespace haf::backend::sfmlb
