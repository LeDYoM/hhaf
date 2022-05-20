#include "sfml_ttfont_factory.hpp"
#include <SFML/Graphics/Font.hpp>
#include "sfml_ttfont.hpp"

using namespace htps;

namespace haf::backend::sfmlb
{
ITTFont* SFMLTTFontFactory::loadFromRawMemory(
    ResourceLoadParameters const& resource_load_parameters)
{
    uptr<sf::Font> font{muptr<sf::Font>()};
    RawMemory internal_raw_memory{resource_load_parameters.raw_memory};
    font->loadFromMemory(internal_raw_memory.data(),
                         internal_raw_memory.size());

    ResourceLoadParameters resource_load_parameters_copy{
        resource_load_parameters.resource_id, htps::move(internal_raw_memory),
        resource_load_parameters.iresource_manager};
    sptr<SFMLTTFont> ttf_font{msptr<SFMLTTFont>(
        htps::move(font), htps::move(resource_load_parameters_copy))};

    font_cache_.push_back(htps::move(ttf_font));
    return (*(font_cache_.end() - 1)).get();
}

SFMLTTFontFactory::~SFMLTTFontFactory()
{
    font_cache_.clear();
    font_cache_.shrink_to_fit();
}
}  // namespace haf::backend::sfmlb
