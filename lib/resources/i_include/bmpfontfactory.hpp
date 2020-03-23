#pragma once

#ifndef LIB_RESOURCES_BMPFONT_FACTORY_HPP
#define LIB_RESOURCES_BMPFONT_FACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/rawmemory.hpp>
#include <mtypes/include/str.hpp>

namespace lib::scene
{
class BMPFont;

class BMPFontFactory final
{
public:
    sptr<BMPFont> loadFromFile(const str &file);
    sptr<BMPFont> loadFromRawMemory(RawMemory *raw_memory);
};
} // namespace lib::scene

#endif
