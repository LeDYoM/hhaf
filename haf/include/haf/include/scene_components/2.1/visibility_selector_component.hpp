HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP
#define HAF_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/properties/property_state.hpp>

#include <haf/include/component/component_declaration.hpp>

#include <haf/include/scene_components/2.1/scene_nodes_component.hpp>

namespace haf::scene
{
/**
 * @brief Component to facilitatee the usage of scenenodes with
 * only one visible node.
 */
class HAF_API VisibilitySelectorComponent final
    : public component::ComponentBase<"VisibilitySelectorComponent",
                                      SceneNodesComponent>
{
public:
    /**
     * @brief Construct a new Visibility Selector Component object
     */
    VisibilitySelectorComponent() noexcept;

    /**
     * @brief Property to set the visible index on a given moment.
     * The index is for the nodes contained in the same SceneNode as this
     * component.
     */
    prop::PropertyState<core::size_type> visible_index;

private:
    void onAttached() override;
    void onNodeAdded(SceneNodeSPtr const& sceneNode);
    void onNodeRemoved(SceneNodeSPtr const& sceneNode);
    void onUpdateVisibleIndex();
    evt::ireceiver m_receiver;
};

}  // namespace haf::scene

#endif
