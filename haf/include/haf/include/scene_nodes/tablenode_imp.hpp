#ifndef HAF_SCENE_TABLENODE_IMP_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_IMP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <haf/include/scene/scenenode.hpp>
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
