#pragma once

#ifndef ZOPER_BOARDUTILS_INCLUDE_HPP
#define ZOPER_BOARDUTILS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/function.hpp>

#include "direction.hpp"

namespace zoper
{

class BoardUtils
{
public:
    static void for_each_token_in_line(
        const lib::vector2dst &startPosition,
        const Direction &direction,
        const lib::vector2dst &board_size,
        lib::function<bool(const lib::vector2dst &, const Direction &)>
            updatePredicate);
};
} // namespace zoper

#endif
