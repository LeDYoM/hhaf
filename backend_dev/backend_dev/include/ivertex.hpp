#ifndef HAF_BACKEND_DEV_IVERTEX_INCLUDE_HPP
#define HAF_BACKEND_DEV_IVERTEX_INCLUDE_HPP

#include <mtypes/include/vector2d.hpp>

namespace haf::backend
{
struct iVertex final
{
    mtps::f32 pos_x;
    mtps::f32 pos_y;
    mtps::u8 r;
    mtps::u8 g;
    mtps::u8 b;
    mtps::f32 tc_x;
    mtps::f32 tc_y;
};

}  // namespace haf::backend

#endif
