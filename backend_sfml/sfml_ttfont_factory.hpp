#ifndef HAF_BACKEND_SFML_TTFONTFACTORY_HPP
#define HAF_BACKEND_SFML_TTFONTFACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/iresourcefactories.hpp>

namespace haf::backend::sfmlb
{
class SFMLTTFont;
class SFMLTTFontFactory : public ITTFontFactory
{
public:
    ITTFont* loadFromRawMemory(htps::RawMemory* raw_memory,
                               IResourceManager* iresource_manager) override;
    ~SFMLTTFontFactory() override;

private:
    htps::vector<htps::sptr<SFMLTTFont>> font_cache_;
};
}  // namespace haf::backend::sfmlb

#endif
