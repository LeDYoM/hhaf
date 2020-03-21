#pragma once

#ifndef HEF_WINDOW_WINDOW_PROPERTIES_INCLUDE_HPP
#define HEF_WINDOW_WINDOW_PROPERTIES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/system/include/idatawrapper.hpp>

namespace mtps = lib;

namespace lib::win
{

class WindowProperties : public sys::IDataWrapper
{
public:
    mtps::BasicProperty<mtps::u32> width;
    mtps::BasicProperty<mtps::u32> height;
    mtps::BasicProperty<mtps::u32> bits_per_pixel;

    void onAttached() override;
};

} // namespace lib::win

#endif
