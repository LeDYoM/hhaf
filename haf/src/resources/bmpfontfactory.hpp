#ifndef HAF_RESOURCES_BMPFONT_FACTORY_HPP
#define HAF_RESOURCES_BMPFONT_FACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rawmemory.hpp>
#include <htypes/include/str.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/ibmpfont.hpp>

namespace haf::res
{
class BMPFont;

class BMPFontFactory final : public backend::IBMPFontFactory
{
public:
    htps::sptr<BMPFont> loadFromFile(const htps::str& file);
    backend::IFont* loadFromRawMemory(htps::RawMemory* raw_memory) override;
};
}  // namespace haf::res

#endif
