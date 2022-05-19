#include "sfml_ttfont_factory.hpp"
#include <SFML/Graphics/Font.hpp>
#include "sfml_ttfont.hpp"

using namespace htps;

namespace haf::backend::sfmlb
{
ITTFont* SFMLTTFontFactory::loadFromRawMemory(
    RawMemory* raw_memory,
    IResourceManager* iresource_manager)
{
    uptr<sf::Font> font{muptr<sf::Font>()};
    RawMemory internal_raw_memory{*raw_memory};
    font->loadFromMemory(internal_raw_memory.data(),
                         internal_raw_memory.size());
    sptr<SFMLTTFont> t{msptr<SFMLTTFont>(
        htps::move(font), htps::move(internal_raw_memory), iresource_manager)};
    font_cache_.push_back(htps::move(t));
    return (*(font_cache_.end() - 1)).get();
}

SFMLTTFontFactory::~SFMLTTFontFactory()
{
    font_cache_.clear();
    font_cache_.shrink_to_fit();
}
}  // namespace haf::backend::sfmlb
