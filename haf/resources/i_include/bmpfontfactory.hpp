#pragma once

#ifndef HAF_RESOURCES_BMPFONT_FACTORY_HPP
#define HAF_RESOURCES_BMPFONT_FACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/rawmemory.hpp>
#include <mtypes/include/str.hpp>

namespace haf::res
{
class BMPFont;

class BMPFontFactory final
{
public:
    mtps::sptr<BMPFont> loadFromFile(const mtps::str &file);
    mtps::sptr<BMPFont> loadFromRawMemory(mtps::RawMemory *raw_memory);
};
} // namespace haf::res

#endif
