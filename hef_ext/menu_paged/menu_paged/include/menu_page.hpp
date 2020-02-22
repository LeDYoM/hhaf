#pragma once

#ifndef HEF_EXT_MENU_PAGE_INCLUDE_HPP
#define HEF_EXT_MENU_PAGE_INCLUDE_HPP

#include <menu_paged/include/menu_paged_option.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene_nodes/include/tablenode.hpp>
#include <lib/scene_nodes/include/scenenodetext.hpp>

#include <mtypes/include/connection.hpp>
#include <lib/scene_components/include/discretetextcomponent.hpp>

namespace lib::scene
{
class MenuPaged;
class MenuPage : public scene::nodes::TableNode<nodes::SceneNodeText>
{
    using BaseClass = scene::nodes::TableNode<nodes::SceneNodeText>;
private:
    void standarizeText(const sptr<ContainedElement> &ntext);
    void goDown();
    void goUp();
    void goLeft();
    void goRight();
    void goSelected();

    bool nodeHasOptions(const size_type y) const noexcept;
    sptr<DiscreteTextComponent> optionsLabelAt(const size_type y) const;
    void setSelectedItem(const size_type index);
    void updateSelection();
    void setColorToLine(const size_type, const scene::Color &);
    vector<s32> optionsSelected() const;

protected:
    using ContainedElement = BaseClass::ContainedElement;

    MenuPaged *parentMenuPaged();
    const MenuPaged *parentMenuPaged() const;

    sptr<IFont> normalFont() const;
    Color normalColor() const;
    Color selectedColor() const;

    size_type m_previouslySelectedItem{0U};
    size_type m_selectedItem{0U};

    ireceiver m_receiver;

public:
    using BaseClass::BaseClass;
    ~MenuPage() override;

    void onCreated() override;
    void configure(vector<sptr<MenuPagedOption>> options,
        PageOptions page_options = PageOptions{});
    size_type SelectedOptionAtRow(const size_type row) const;

    emitter<const s32> Forward;
    emitter<vector<s32>> Accepted;
    emitter<> Back;
    emitter<vector<s32>> Canceled;
    emitter<const size_type, const s32> Selection;
};

} // namespace lib::scene

#endif
