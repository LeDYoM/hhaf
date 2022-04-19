#ifndef HAF_BACKEND_SFML_TTFONTFACTORY_HPP
#define HAF_BACKEND_SFML_TTFONTFACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/iresourcefactories.hpp>
#include "ttfont.hpp"

namespace haf::backend::sfmlb
{
class TTFontFactory : public ITTFontFactory
{
public:
    ITTFont* loadFromRawMemory(htps::RawMemory* raw_memory) override;
    ~TTFontFactory() override;

private:
    htps::vector<htps::uptr<TTFont>> font_cache_;
};
}  // namespace haf::backend::sfmlb

#endif
