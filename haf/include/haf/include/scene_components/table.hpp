HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENTS_TABLE_INCLUDE_HPP
#define HAF_COMPONENTS_TABLE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <facil_math/include/vector_types.hpp>
#include <haf/include/properties/iproperty.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/haf_export.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/component/component.hpp>

namespace haf::scene
{
/**
 * @brief class Node with implementation details for a Table node.
 */
class HAF_API Table : public component::Component
{
    using BaseClass = component::Component;

public:
    using BaseClass::BaseClass;

    prop::PropertyState<fmath::vector2dst> TableSize;
    prop::PropertyState<fmath::vector2df> TableSizeForNodes;

    evt::emitter<fmath::vector2dst, htps::sptr<SceneNode> const&>
        onInnerNodeCreated;

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
    htps::sptr<SceneNode> innerSceneNodeAt(fmath::vector2dst const index) const;

    virtual void setTableSize(fmath::vector2dst const ntableSize);

    void for_each_table_innerSceneNode(
        htps::function<void(const fmath::vector2dst&, htps::sptr<SceneNode>&)>
            action);

private:
    void createInnerSceneNodeAt(fmath::vector2dst const index,
                                htps::str const& name);

    void setInnerSceneNodeAt(fmath::vector2dst const index,
                             htps::sptr<SceneNode>& scene_node);

    void updateTableSizeIfNecessary();

    virtual void createNodeAt(fmath::vector2dst const& index) = 0;

    htps::vector<htps::vector<htps::sptr<SceneNode>>> m_inner_nodes;
};

}  // namespace haf::scene

#endif
