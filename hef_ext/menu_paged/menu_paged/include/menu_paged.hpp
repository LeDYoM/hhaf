#pragma once

#ifndef HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/color.hpp>
#include <lib/resources/include/ifont.hpp>

namespace lib::scene
{
class MenuPage;

/// Main class to model a menu in paged style.
/// This class should be used as a base class for a new
/// type of @b SceneNode.
class MenuPaged : public SceneNode
{
public:
    using BaseClass = SceneNode;
    MenuPaged(SceneNode* parent, mtps::str name);
    ~MenuPaged() override;

    void setNormalTextFont(mtps::sptr<IFont> normal_text_font);
    mtps::sptr<IFont> normalTextFont() const noexcept;

    void setNormalColor(Color normal_color);
    Color normalColor() const;

    void setSelectedColor(Color selected_color);
    Color selectedColor() const;

    void setSceneNodeSizeForPages( mtps::vector2df size);
     mtps::vector2df sceneNodeSizeForPages() const;
    void setMenuPagedStatus(mtps::s32 status);
    mtps::s32 status() const;

    void terminate(const mtps::s32 status);

    mtps::emitter<const mtps::s32> MenuFinished;

protected:
    mtps::sptr<MenuPage> createMenuPage(mtps::str name);
    void configure_menu(mtps::vector_shared_pointers<MenuPage> menu_steps);

    template <typename... Args>
    mtps::sptr<MenuPage> createAndConfigureMenuPage(mtps::str name, Args&&... args)
    {
        auto node{createMenuPage(std::move(name))};
        node->sceneNodeSize = scene_node_size_for_pages_;
        node->configure(std::forward<Args>(args)...);
        return node;
    }

private:
    mtps::vector2df scene_node_size_for_pages_;
    mtps::sptr<IFont> normal_text_font_;
    Color normal_color_;
    Color selected_color_;
    mtps::vector_shared_pointers<MenuPage> menu_steps_;
    mtps::s32 status_{};
};
} // namespace lib

#endif
