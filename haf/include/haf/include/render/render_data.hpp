HAF_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDERDATA_INCLUDE_HPP
#define HAF_RENDER_RENDERDATA_INCLUDE_HPP

#include <haf/include/core/types.hpp>

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

}  // namespace haf::render

#endif
