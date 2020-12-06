#ifndef HAF_SCENE_RENDERIZABLE_MODIFIER_CONTEXT_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_MODIFIER_CONTEXT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/vector2d.hpp>
#include <haf/render/include/vertex.hpp>

namespace haf::scene
{
struct RenderizableModifierContext
{
    const mtps::Rectf32 box;
    const mtps::Rects32 texture_rect;
    const mtps::vector2du32 texture_size;
    const Vertex vertex;
    constexpr mtps::vector2df normalizedVertexInBox() const
    {
        return (box.rightBottom() - vertex.position) / box.rightBottom();
    }
};
}  // namespace haf::scene

#endif
