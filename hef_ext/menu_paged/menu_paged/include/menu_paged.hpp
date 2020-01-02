#pragma once

#ifndef HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

#include <lib/scene/scenenode.hpp>
#include <lib/include/resources/ifont.hpp>
#include <lib/scene/color.hpp>

namespace lib::scene
{
class MenuPage;

/// Main class to model a menu in paged style.
/// This class should be used as a base class for a new
/// type of @b SceneNode.
class MenuPaged : public SceneNode
{
public:
    using SceneNode::SceneNode;
    ~MenuPaged() override;

    void setNormalTextFont(sptr<IFont> normal_text_font);
    sptr<IFont> normalTextFont() const noexcept;

    void setNormalColor(Color normal_color);
    Color normalColor() const;

    void setSelectedColor(Color selected_color);
    Color selectedColor() const;

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
        node->configure(std::forward<Args>(args)...);
        return node;
    }

private:
    void showPage(const s32 page_index);
    void hidePage(const s32 page_index);

    sptr<IFont> normal_text_font_;
    Color normal_color_;
    Color selected_color_;
    vector_shared_pointers<MenuPage> menu_steps_;
    s32 status_{0};
};
} // namespace lib

#endif
