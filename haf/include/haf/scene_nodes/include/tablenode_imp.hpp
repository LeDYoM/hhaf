#ifndef HAF_SCENE_TABLENODE_IMP_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_IMP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene_nodes/include/tablenode_properties.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene::nodes
{
class TableNodeImp : public SceneNode, public TableNodeProperties
{
public:
    using BaseClass = SceneNode;
    using SceneNode::SceneNode;
    using SceneNode::prop;
    using TableNodeProperties::prop;

    ~TableNodeImp() override;

    htps::vector2df cellSize() const;

    void update() override;

protected:
    void setInnerSceneNodeAt(htps::vector2dst const index,
                             htps::sptr<SceneNode> scene_node);

    void updateTableSizeIfNecessary();
    virtual void setTableSize(htps::vector2dst const ntableSize);

private:
    void for_each_table_innerSceneNode(
        htps::function<void(const htps::vector2dst&,
                            const htps::sptr<SceneNode>&)> action);

    htps::vector<htps::vector_shared_pointers<SceneNode>> inner_nodes_;
};
}  // namespace haf::scene::nodes

#endif
