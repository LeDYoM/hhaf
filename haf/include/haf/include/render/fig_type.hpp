#ifndef HAF_RENDER_FIG_TYPE_T_HPP
#define HAF_RENDER_FIG_TYPE_T_HPP

#include <htypes/include/types.hpp>

namespace haf::render
{
enum class FigType_t : htps::u8
{
    Quad,
    Shape,
    EmptyQuad
};
}  // namespace haf::render

#endif