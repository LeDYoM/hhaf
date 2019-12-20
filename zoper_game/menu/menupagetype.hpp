#pragma once

#ifndef ZOPER_MENUPAGETYPE_INCLUDE_HPP__
#define ZOPER_MENUPAGETYPE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>

namespace zoper
{
enum class MenuPageType : lib::u32
{
    Main = 0U,
    SelectLevelToken = 1U,
    SelectLevelSpeed = 2U,
    Options = 3
};
}

#endif