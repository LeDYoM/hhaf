HAF_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDERDATA_INCLUDE_HPP
#define HAF_RENDER_RENDERDATA_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/math/types.hpp>

namespace haf::render
{
struct RenderData
{
    core::u32 vao;
    core::u32 textureId;
    core::u32 shader;
    core::u32 sizeCount;

    void render() const;
};

using RenderDataVector = core::vector<RenderData>;

struct FrameRenderStartData
{
    math::vector4df backgroundColor;
};

struct FrameRenderData
{
    RenderDataVector elements;
};

}  // namespace haf::render

#endif
