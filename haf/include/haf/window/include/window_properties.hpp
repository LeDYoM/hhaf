#pragma once

#ifndef HEF_WINDOW_WINDOW_PROPERTIES_INCLUDE_HPP
#define HEF_WINDOW_WINDOW_PROPERTIES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <haf/system/include/idatawrapper.hpp>

namespace haf::win
{

class WindowProperties : public sys::IDataWrapper
{
public:
    mtps::BasicProperty<mtps::u32> width;
    mtps::BasicProperty<mtps::u32> height;
    mtps::BasicProperty<mtps::u8> bits_per_red;
    mtps::BasicProperty<mtps::u8> bits_per_green;
    mtps::BasicProperty<mtps::u8> bits_per_blue;
    mtps::BasicProperty<mtps::u8> bits_per_alpha;

    mtps::u32 bitsPerPixel() const;

    void onAttached() override;
};

} // namespace haf::win

#endif
