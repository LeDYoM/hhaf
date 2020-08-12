#pragma once

#ifndef HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/color.hpp>
#include <haf/resources/include/ifont.hpp>
#include "menu_paged_properties.hpp"
#include "menu_page.hpp"

namespace haf::scene
{
/**
 * @brief Main class to model a menu in paged style.
 * This class should be used as a base class for a new type of @b SceneNode.
 */
class MenuPaged : public SceneNode, MenuPagedProperties
{
public:
    using BaseClass = SceneNode;
    using SceneNode::SceneNode;

    using MenuPagedProperties::prop;

    ~MenuPaged() override;

    void setMenuPagedStatus(const mtps::s32 status);
    mtps::s32 status() const;

    void terminate(const mtps::s32 status);

    mtps::emitter<const mtps::s32> MenuFinished;

    void update() override;

protected:
    mtps::sptr<MenuPage> createMenuPage(mtps::str name);
    void configure_menu(mtps::vector_shared_pointers<MenuPage> menu_steps);

    template <typename... Args>
    mtps::sptr<MenuPage> createAndConfigureMenuPage(mtps::str name,
                                                    Args&&... args)
    {
        auto node{createMenuPage(std::move(name))};
        node->configure(std::forward<Args>(args)...);
        return node;
    }

private:
    mtps::vector_shared_pointers<MenuPage> menu_steps_;
    mtps::s32 status_{};
};
}  // namespace haf::scene

#endif
