#ifndef HAF_BACKEND_SFML_TTFONT_INCLUDE_HPP
#define HAF_BACKEND_SFML_TTFONT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/rect.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/rawmemory.hpp>
#include <backend_dev/include/ittfont.hpp>
#include <backend_dev/include/iresource_manager.hpp>
#include <backend_dev/include/resource_load_parameters.hpp>
#include <map>

namespace sf
{
class Font;
}
namespace haf::backend::sfmlb
{
class SFMLTexture;
class SFMLTTFont : public ITTFont
{
public:
    SFMLTTFont(htps::uptr<sf::Font> f,
               ResourceLoadParameters&& resource_load_parameters);
    ~SFMLTTFont() override;

    fmath::Rectf32 getBounds(const htps::u32 codePoint,
                            const htps::u32 characterSize) const override;
    fmath::Rectf32 getTextureBounds(
        const htps::u32 codePoint,
        const htps::u32 characterSize) const override;
    htps::f32 getAdvance(const htps::u32 codePoint,
                         const htps::u32 characterSize) const override;
    htps::f32 getLineSpacing(const htps::u32 characterSize) const override;
    htps::f32 getKerning(const htps::u32 first,
                         const htps::u32 second,
                         const htps::u32 characterSize) const override;
    htps::str getTexture(const htps::u32 characterSize,
                         char const character) override;

private:
    htps::uptr<sf::Font> font_;
    // We need the raw memory of the loaded font to be kept in memory.
    htps::RawMemory raw_memory_;
    IResourceManager* iresource_manager_;
    htps::str resource_id_;
    std::map<htps::u32, htps::sptr<SFMLTexture>> font_textures_cache_;
    std::map<htps::u32, htps::str> textures_ids_cache_;
};
}  // namespace haf::backend::sfmlb

#endif
