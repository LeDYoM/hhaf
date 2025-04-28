#include "sfml_ttfont.hpp"
#include "conversions.hpp"
#include <SFML/Graphics/Font.hpp>

using namespace htps;
using namespace fmath;

namespace haf::backend::sfmlb
{
SFMLTTFont::SFMLTTFont(uptr<sf::Font> font,
                       ResourceLoadParameters&& resource_load_parameters) :
    font_{htps::move(font)},
    raw_memory_{htps::move(resource_load_parameters.raw_memory)},
    iresource_manager_{htps::move(resource_load_parameters.iresource_manager)},
    resource_id_{htps::move(resource_load_parameters.resource_id)}
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
        // That is needed here is to force the load of the font surface
        // TODO: Check if it is still needed
        for (u32 i{0U}; i < 0xFF; ++i)
        {
            (void)(getTextureBounds(i, characterSize));
        }

        auto new_texture{
            msptr<SFMLTexture>(&font_->getTexture(characterSize), false)};

        str complete_resource_id{make_str(resource_id_, characterSize)};
        bool result{iresource_manager_->setExternalTexture(complete_resource_id,
                                                           new_texture.get())};
        if (result)
        {
            textures_ids_cache_[characterSize]  = complete_resource_id;
            font_textures_cache_[characterSize] = new_texture;
            return complete_resource_id;
        }
    }
    return "";
}
}  // namespace haf::backend::sfmlb
