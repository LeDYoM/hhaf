HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP
#define HAF_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/propertystate.hpp>

#include <haf/include/component/component.hpp>

namespace haf::scene
{
/**
 * @brief Component to facilitatee the usage of scenenodes with
 * only one visible node.
 */
class VisibilitySelectorComponent : public component::Component
{
public:
    /**
     * @brief Construct a new Visibility Selector Component object
     */
    VisibilitySelectorComponent();

    /**
     * @brief Update function
     */
    void update() override;

    /**
     * @brief Property to set the visible index on a given moment.
     * The index is for the nodes contained in the same SceneNode as this
     * component.
     */
    htps::PropertyState<htps::size_type> visible_index;
};

}  // namespace haf::scene

#endif
