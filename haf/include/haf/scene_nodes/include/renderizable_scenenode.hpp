#pragma once

#ifndef HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/scene/include/renderizable_builder.hpp>
#include <haf/scene/include/scenenode.hpp>

namespace haf::scene
{
class Renderizable;

class RenderizableSceneNode : public SceneNode
{
public:
    using BaseClass = SceneNode;

    RenderizableSceneNode(mtps::rptr<SceneNode> parent, const mtps::str& name);
    void buildNode(RenderizableBuilder& node_builder);

    mtps::sptr<Renderizable> node() noexcept;
    const mtps::sptr<Renderizable> node() const noexcept;

private:
    mtps::sptr<Renderizable> node_;
};
}  // namespace haf::scene

#endif
