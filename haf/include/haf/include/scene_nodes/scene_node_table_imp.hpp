HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_NODE_TABLE_IMP_INCLUDE_HPP
#define HAF_SCENE_SCENE_NODE_TABLE_IMP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/properties/iproperty.hpp>

#include <haf/include/haf_export.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/component/component.hpp>

namespace haf::scene::nodes
{
/**
 * @brief class Node with implementation details for a Table node.
 */
class HAF_API TableNodeImp : public TransformableSceneNode
{
    using BaseClass = TransformableSceneNode;

public:
    using TransformableSceneNode::TransformableSceneNode;  ///< Inherited
                                                           ///< constuctor

    using ContainedType_t = htps::sptr<TransformableSceneNode>;

    prop::PropertyState<fmath::vector2dst> TableSize;
    prop::PropertyState<fmath::vector2df> TableSizeForNodes;

    evt::emitter<fmath::vector2dst, ContainedType_t const&> onInnerNodeCreated;

    /**
     * @brief Get the size of each cell.
     * @note It might change when new size for the table is set
     * @return fmath::vector2df The size of each cell
     */
    fmath::vector2df cellSize() const;

    /**
     * @brief Update the node
     */
    void update() override;

    bool nodeTableCreated(fmath::vector2dst const& index) const;

    virtual void onAllTableElementsCreated(fmath::vector2dst const);
    evt::emitter<fmath::vector2dst const> allTableElementsCreated;

    void createTableNodesIfNecessary();

protected:

    ContainedType_t innerSceneNodeAt(fmath::vector2dst const index) const;

    virtual void setTableSize(fmath::vector2dst const ntableSize);

private:
    ContainedType_t createInnerSceneNodeAt(fmath::vector2dst const index,
                                           htps::str const& name);

    void setInnerSceneNodeAt(fmath::vector2dst const index,
                             ContainedType_t& scene_node);

    void updateTableSizeIfNecessary();

    void for_each_table_innerSceneNode(
        htps::function<void(const fmath::vector2dst&, ContainedType_t&)> action);

    virtual void createNodeAt(fmath::vector2dst const& index) = 0;

    htps::vector<htps::vector<ContainedType_t>> inner_nodes_;
};

}  // namespace haf::scene::nodes

#endif
