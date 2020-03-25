#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/icomponent.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <lib/include/liblog.hpp>

#include "scenenode.hpp"

namespace lib::scene
{
class RenderizableSceneNode : public SceneNode
{
public:
    using BaseClass = SceneNode;

    template <typename... Args>
    RenderizableSceneNode(mtps::rptr<SceneNode> parent, const mtps::str&name, Args &&... args)
        : SceneNode{std::move(parent), name},
          node_{createRenderizable(name + "_node", std::forward<Args>(args)...)}
    {
    }

    mtps::sptr<Renderizable> node() noexcept { return node_; }
    const mtps::sptr<Renderizable> node() const noexcept { return node_; }

private:
    mtps::sptr<Renderizable> node_;
};
} // namespace lib::scene

#endif
