#ifndef HAF_SCENE_TABLENODE_IMP_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_IMP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <haf/include/scene/transformable_scenenode.hpp>
#include <haf/include/scene_nodes/tablenode_properties.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene::nodes
{
/**
 * @brief class Node with implementation details for a Table node.
 */
class TableNodeImp : public SceneNode, public TableNodeProperties
{
    using BaseClass = SceneNode;
public:
    using SceneNode::SceneNode;         ///< Inherited constuctor
    using SceneNode::prop;              ///< Properties from @b SceneNode
    using TableNodeProperties::prop;    ///< Properties TableNodeProperties

    using ContainedType_t = htps::sptr<TransformableSceneNode>;

    /**
     * @brief Get the size of each cell.
     * @note It might change when new size for the table is set
     * @return htps::vector2df The size of each cell
     */
    htps::vector2df cellSize() const;

    /**
     * @brief Update the node
     * 
     */
    void update() override;

protected:
    void setInnerSceneNodeAt(htps::vector2dst const index,
                             ContainedType_t scene_node);

    void updateTableSizeIfNecessary();
    virtual void setTableSize(htps::vector2dst const ntableSize);

private:
    void for_each_table_innerSceneNode(
        htps::function<void(const htps::vector2dst&,
                            ContainedType_t&)> action);

    htps::vector<htps::vector<ContainedType_t>> inner_nodes_;
};

}  // namespace haf::scene::nodes

#endif
