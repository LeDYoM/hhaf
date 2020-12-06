#ifndef HAF_SCENE_FIG_TYPE_T_HPP
#define HAF_SCENE_FIG_TYPE_T_HPP

#include <mtypes/include/types.hpp>

namespace haf::scene
{
enum class FigType_t : mtps::u8
{
    Quad,
    Shape,
    EmptyQuad
};
}  // namespace haf::scene

#endif