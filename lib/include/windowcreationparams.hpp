#pragma once

#ifndef LIB_WINDOWCREATIONPARAMS_INCLUDE_HPP
#define LIB_WINDOWCREATIONPARAMS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib
{
    struct WindowCreationParams
    {
        const str windowTitle;
        u32 width{ 1024 };
        u32 height{ 768 };
        u32 bpp{ 16 };
        u32 antialiasing{ 0 };
        bool vsync{ false };
        bool fullScreen{ false };
        bool resizable{ false };
    };
}

#endif
