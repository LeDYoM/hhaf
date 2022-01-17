#ifndef HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/connection.hpp>

#include <haf/include/scene/transformable_scene_node.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/resources/ifont.hpp>
#include "menu_paged_properties.hpp"
#include "menu_page.hpp"

namespace haf::scene
{
enum class MenuFinishedStatus : htps::u8
{
    Backward,
    Forward
};

/**
 * @brief Main class to model a menu in paged style.
 */
class MenuPaged : public TransformableSceneNode, MenuPagedProperties
{
    using BaseClass = TransformableSceneNode;

public:
    using TransformableSceneNode::TransformableSceneNode;

    using TransformableSceneNode::prop;
    using MenuPagedProperties::prop;

    ~MenuPaged() override;

    void setMenuPagedStatus(MenuFinishedStatus const status);
    MenuFinishedStatus status() const;

    void terminate(MenuFinishedStatus const status);

    htps::emitter<const MenuFinishedStatus> MenuFinished;

    void update() override;

protected:
    htps::sptr<MenuPage> createMenuPage(htps::str name);
    void configure_menu(htps::vector_shared_pointers<MenuPage> menu_steps);

    template <typename... Args>
    htps::sptr<MenuPage> createAndConfigureMenuPage(htps::str name,
                                                    Args&&... args)
    {
        auto node{createMenuPage(std::move(name))};
        node->configure(std::forward<Args>(args)...);
        return node;
    }

private:
    htps::vector_shared_pointers<MenuPage> menu_steps_;
    MenuFinishedStatus status_{MenuFinishedStatus::Backward};
};
}  // namespace haf::scene

#endif
