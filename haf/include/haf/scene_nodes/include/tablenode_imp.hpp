#pragma once

#ifndef HAF_SCENE_TABLENODE_IMP_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_IMP_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene_nodes/include/tablenode_properties.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene::nodes
{
class TableNodeImp : public SceneNode, public TableNodeProperties
{
public:
    using BaseClass = SceneNode;
    using BaseClass::BaseClass;
    using BaseClass::prop;
    using TableNodeProperties::prop;

    ~TableNodeImp() override;

    mtps::vector2df cellSize() const;

    void update() override;

protected:
    void setInnerSceneNodeAt(mtps::vector2dst const index,
                             mtps::sptr<SceneNode> scene_node);

    void updateTableSizeIfNecessary();
    virtual void setTableSize(mtps::vector2dst const ntableSize);

private:
    void for_each_table_innerSceneNode(
        mtps::function<void(const mtps::vector2dst&,
                            const mtps::sptr<SceneNode>&)> action);

    mtps::vector<mtps::vector_shared_pointers<SceneNode>> inner_nodes_;
};
}  // namespace haf::scene::nodes

#endif
