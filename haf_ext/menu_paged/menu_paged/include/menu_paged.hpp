#ifndef HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/connection.hpp>

#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/resources/ifont.hpp>
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
    using SceneNode::prop;

    ~MenuPaged() override;

    void setMenuPagedStatus(const htps::s32 status);
    htps::s32 status() const;

    void terminate(const htps::s32 status);

    htps::emitter<const htps::s32> MenuFinished;

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
    htps::s32 status_{};
};
}  // namespace haf::scene

#endif
