#pragma once

#ifndef HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

#include <lib/scene/scenenode.hpp>
#include <lib/scene/color.hpp>
#include <lib/include/resources/ifont.hpp>

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
    MenuPaged(SceneNode* parent, str name);
    ~MenuPaged() override;

    void setNormalTextFont(sptr<IFont> normal_text_font);
    sptr<IFont> normalTextFont() const noexcept;

    void setNormalColor(Color normal_color);
    Color normalColor() const;

    void setSelectedColor(Color selected_color);
    Color selectedColor() const;

    void setSceneNodeSizeForPages(vector2df size);
    vector2df sceneNodeSizeForPages() const;
    void setMenuPagedStatus(s32 status);
    s32 status() const;

    void terminate(const s32 status);

    emitter<const s32> MenuFinished;

protected:
    sptr<MenuPage> createMenuPage(str name);
    void configure_menu(vector_shared_pointers<MenuPage> menu_steps);

    template <typename... Args>
    sptr<MenuPage> createAndConfigureMenuPage(str name, Args&&... args)
    {
        auto node{createMenuPage(std::move(name))};
        node->sceneNodeSize = scene_node_size_for_pages_;
        node->configure(std::forward<Args>(args)...);
        return node;
    }

private:
    vector2df scene_node_size_for_pages_;
    sptr<IFont> normal_text_font_;
    Color normal_color_;
    Color selected_color_;
    vector_shared_pointers<MenuPage> menu_steps_;
    s32 status_{0};
};
} // namespace lib

#endif
