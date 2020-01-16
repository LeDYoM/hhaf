#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/icomponent.hpp>
#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/scene/components/renderizables.hpp>
#include <lib/include/liblog.hpp>

#include "scenenode.hpp"

namespace lib::scene
{
class RenderizableSceneNode : public SceneNode
{
public:
    using BaseClass = SceneNode;

    template <typename... Args>
    RenderizableSceneNode(SceneNode *const parent, const str& name, Args &&... args)
        : SceneNode{parent, name},
          m_node{addComponentOfType<Renderizables>()
                     ->createRenderizable(name + "_node", std::forward<Args>(args)...)}
    {
    }

    sptr<Renderizable> node() noexcept { return m_node; }
    const sptr<Renderizable> node() const noexcept { return m_node; }

private:
    sptr<Renderizable> m_node;
};
} // namespace lib::scene

#endif
