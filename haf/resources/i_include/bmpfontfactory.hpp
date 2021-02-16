#ifndef HAF_RESOURCES_BMPFONT_FACTORY_HPP
#define HAF_RESOURCES_BMPFONT_FACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rawmemory.hpp>
#include <htypes/include/str.hpp>

namespace haf::res
{
class BMPFont;

class BMPFontFactory final
{
public:
    mtps::sptr<BMPFont> loadFromFile(const mtps::str& file);
    mtps::sptr<BMPFont> loadFromRawMemory(mtps::RawMemory* raw_memory);
};
}  // namespace haf::res

#endif
