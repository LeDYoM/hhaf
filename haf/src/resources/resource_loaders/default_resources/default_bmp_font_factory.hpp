HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_DEFAULT_BMP_FONT_FACTORY_HPP
#define HAF_RESOURCES_DEFAULT_BMP_FONT_FACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rawmemory.hpp>
#include <htypes/include/str.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/ibmp_font.hpp>
#include <backend_dev/include/resource_load_parameters.hpp>

namespace haf::res
{
class DefaultBMPFont;

class DefaultBMPFontFactory final : public backend::IBMPFontFactory
{
public:
    backend::IBMPFont* loadFromRawMemory(backend::ResourceLoadParameters const&
                                             resource_load_parameters) override;

private:
    htps::vector<htps::sptr<DefaultBMPFont>> bmpfont_cache_;
};
}  // namespace haf::res

#endif
