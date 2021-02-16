#ifndef HAF_SCENE_SCENENODESGROUP_INCLUDE_HPP
#define HAF_SCENE_SCENENODESGROUP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>

namespace haf::scene
{
class SceneNode;

class SceneNodesGroup
{
public:
    using SceneNodeVector = htps::vector<htps::sptr<SceneNode>>;
    void addSceneNode(mtps::sptr<SceneNode> node);
    bool removeSceneNode(mtps::sptr<SceneNode> element);
    void clearSceneNodes();

    SceneNodeVector const& sceneNodes() const noexcept;
    SceneNodeVector& sceneNodes() noexcept;

private:
    SceneNodeVector groups_;
};

}  // namespace haf::scene

#endif
