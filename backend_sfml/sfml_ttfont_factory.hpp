#ifndef HAF_BACKEND_SFML_TTFONTFACTORY_HPP
#define HAF_BACKEND_SFML_TTFONTFACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/resource_load_parameters.hpp>

namespace haf::backend::sfmlb
{
class SFMLTTFont;
class SFMLTTFontFactory : public ITTFontFactory
{
public:
    ITTFont* loadFromRawMemory(
        ResourceLoadParameters const& resource_load_parameters) override;
    ~SFMLTTFontFactory() override;

private:
    htps::vector<htps::sptr<SFMLTTFont>> font_cache_;
};
}  // namespace haf::backend::sfmlb

#endif
