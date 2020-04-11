#pragma once

#ifndef HAF_SCENE_SCENENODES_INCLUDE_HPP
#define HAF_SCENE_SCENENODES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/vector.hpp>
#include <haf/scene/include/icomponent.hpp>
#include <haf/scene/include/componentcontainer.hpp>

namespace haf::scene
{
class SceneNodesGroup
{
public:
    void addSceneNode(mtps::sptr<SceneNode> node);
    void removeSceneNode(mtps::sptr<SceneNode> element);
    void clearSceneNodes();

    void renderGroups(const bool parentTransformationChanged);

    constexpr const auto& sceneNodes() const noexcept { return m_groups; }
    constexpr auto& sceneNodes() noexcept { return m_groups; }

private:
    mtps::vector<mtps::sptr<SceneNode>> m_groups;
};

}  // namespace haf::scene

#endif
