HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_NODE_TABLE_IMP_INCLUDE_HPP
#define HAF_SCENE_SCENE_NODE_TABLE_IMP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <haf/include/properties/iproperty.hpp>
#include <haf/include/properties/property_state.hpp>

#include <haf/include/haf_export.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/scene/scene_node.hpp>
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

    void addRequirements(component::ComponentRequirements&) override;

    prop::PropertyState<fmath::vector2dst> TableSize;
    prop::PropertyState<fmath::vector2df> TableSizeForNodes;

    evt::emitter<fmath::vector2dst, SceneNodeSPtr const&> onInnerNodeCreated;

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
    evt::emitter<fmath::vector2dst const> allTableElementsCreated;

    void createTableNodesIfNecessary();

protected:
    SceneNodeSPtr innerSceneNodeAt(fmath::vector2dst const index) const;

    virtual void setTableSize(fmath::vector2dst const ntableSize);

private:
    SceneNodeSPtr createInnerSceneNodeAt(fmath::vector2dst const index,
                                         htps::str const& name);

    void setInnerSceneNodeAt(fmath::vector2dst const index,
                             SceneNodeSPtr& scene_node);

    void updateTableSizeIfNecessary();

    void for_each_table_innerSceneNode(
        htps::function<void(const fmath::vector2dst&, SceneNodeSPtr&)> action);

    virtual void createNodeAt(fmath::vector2dst const& index) = 0;

    htps::vector<htps::vector<SceneNodeSPtr>> m_inner_nodes;
};

}  // namespace haf::scene

#endif
