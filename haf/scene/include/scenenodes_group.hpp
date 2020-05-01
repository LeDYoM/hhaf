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
class SceneNode;

class SceneNodesGroup
{
public:
    using InnerType = mtps::vector<mtps::sptr<SceneNode>>;

    void addSceneNode(mtps::sptr<SceneNode> node);
    void removeSceneNode(mtps::sptr<SceneNode> element);
    void clearSceneNodes();

    void renderGroups(const bool parentTransformationChanged);

    const InnerType& sceneNodes() const noexcept;
    InnerType& sceneNodes() noexcept;

private:
    InnerType m_groups;
};

}  // namespace haf::scene

#endif
