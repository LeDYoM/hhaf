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
        const mtps::vector2dst &startPosition,
        const Direction &direction,
        const mtps::vector2dst &board_size,
        mtps::function<bool(const mtps::vector2dst &, const Direction &)>
            updatePredicate);
};
} // namespace zoper

#endif
