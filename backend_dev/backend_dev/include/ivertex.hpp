#ifndef HAF_BACKEND_DEV_IVERTEX_INCLUDE_HPP
#define HAF_BACKEND_DEV_IVERTEX_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

namespace haf::backend
{
struct iVertex final
{
    htps::f32 pos_x;
    htps::f32 pos_y;
    htps::u8 r;
    htps::u8 g;
    htps::u8 b;
    htps::u8 a;
    htps::f32 tc_x;
    htps::f32 tc_y;
};

using iPosition = htps::vector2d<htps::f32>;
using iTextureCoordinates = htps::vector2d<htps::f32>;

struct iColor final
{
    htps::u8 r;
    htps::u8 g;
    htps::u8 b;
    htps::u8 a;
};

}  // namespace haf::backend

#endif
