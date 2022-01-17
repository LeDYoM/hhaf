#ifndef HTPS_TYPES_CAST_INCLUDE_HPP
#define HTPS_TYPES_CAST_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace htps
{
template <typename T, typename Y>
T d_cast(Y* element)
{
    return dynamic_cast<T>(element);
}

}  // namespace htps

#endif
