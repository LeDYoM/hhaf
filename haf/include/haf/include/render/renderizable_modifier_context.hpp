#ifndef HAF_SCENE_RENDERIZABLE_MODIFIER_CONTEXT_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_MODIFIER_CONTEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/render/vertex.hpp>

namespace haf::render
{
struct RenderizableModifierContext
{
    const htps::Rectf32 box;
    const htps::Rects32 texture_rect;
    const htps::vector2du32 texture_size;
    const Vertex vertex;
    constexpr htps::vector2df normalizedVertexInBox() const
    {
        return (box.rightBottom() - vertex.position) / box.rightBottom();
    }
};
}  // namespace haf::render

#endif
