HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_NODE_TABLE_IMP_INCLUDE_HPP
#define HAF_SCENE_SCENE_NODE_TABLE_IMP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties/iproperty.hpp>

#include <haf/include/haf_export.hpp>
#include <htypes/include/connection.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_requirements.hpp>

namespace haf::scene
{
/**
 * @brief class Node with implementation details for a Table node.
 */
class HAF_API TableNodeImp : public component::Component
{
    using BaseClass = component::Component;

public:
    using BaseClass::BaseClass;

    using ContainedType_t = htps::sptr<TransformableSceneNode>;

    void addRequirements(component::ComponentRequirements&) override;

    htps::PropertyState<htps::vector2dst> TableSize;
    htps::PropertyState<htps::vector2df> TableSizeForNodes;

    htps::emitter<htps::vector2dst, ContainedType_t const&> onInnerNodeCreated;

    /**
     * @brief Get the size of each cell.
     * @note It might change when new size for the table is set
     * @return htps::vector2df The size of each cell
     */
    htps::vector2df cellSize() const;

    /**
     * @brief Update the node
     */
    void update() override;

    bool nodeTableCreated(htps::vector2dst const& index) const;
    htps::emitter<htps::vector2dst const> allTableElementsCreated;

    void createTableNodesIfNecessary();

protected:
    ContainedType_t innerSceneNodeAt(htps::vector2dst const index) const;

    virtual void setTableSize(htps::vector2dst const ntableSize);

private:
    ContainedType_t createInnerSceneNodeAt(htps::vector2dst const index,
                                           htps::str const& name);

    void setInnerSceneNodeAt(htps::vector2dst const index,
                             ContainedType_t& scene_node);

    void updateTableSizeIfNecessary();

    void for_each_table_innerSceneNode(
        htps::function<void(const htps::vector2dst&, ContainedType_t&)> action);

    virtual void createNodeAt(htps::vector2dst const& index) = 0;

    htps::vector<htps::vector<ContainedType_t>> inner_nodes_;
//    htps::sptr<TransformableComponent> m_transformableComponent;
};

}  // namespace haf::scene

#endif
