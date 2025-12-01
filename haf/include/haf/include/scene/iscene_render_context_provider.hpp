HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_ISCENE_RENDER_CONTEXT__PROVIDER_INCLUDE_HPP
#define HAF_SCENE_ISCENE_RENDER_CONTEXT__PROVIDER_INCLUDE_HPP

import htypes;

#include <haf/include/scene/scene_render_context.hpp>

namespace haf::scene
{
class ISceneRenderContextProvider
{
protected:
    ~ISceneRenderContextProvider() = default;
public:
    virtual SceneRenderContext& sceneRenderContext() = 0;
    virtual SceneRenderContext const& sceneRenderContext() const = 0;
};

}  // namespace haf::scene

#endif
