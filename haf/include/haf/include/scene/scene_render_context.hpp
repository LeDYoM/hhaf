HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_CONTEXT_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_CONTEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::scene
{
struct SceneRenderContext
{
    bool parentTransformationChanged_{false};
    Matrix4x4 currentTransformation{Matrix4x4::Identity};

    void reset()
    {
        *this = SceneRenderContext{};
    }
};

}  // namespace haf::scene

#endif
