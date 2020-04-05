#pragma once

#ifndef HEF_EXT_MENU_PAGE_INCLUDE_HPP
#define HEF_EXT_MENU_PAGE_INCLUDE_HPP

#include <menu_paged/include/menu_paged_option.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene_nodes/include/tablenode.hpp>
#include <lib/scene_nodes/include/scenenodetext.hpp>

#include <mtypes/include/connection.hpp>
#include <lib/scene_components/include/discretetextcomponent.hpp>

namespace haf::scene
{
class MenuPaged;
class MenuPage : public scene::nodes::TableNode<nodes::SceneNodeText>
{
    using BaseClass = scene::nodes::TableNode<nodes::SceneNodeText>;
private:
    void standarizeText(const mtps::sptr<ContainedElement> &ntext);
    void goDown();
    void goUp();
    void goLeft();
    void goRight();
    void goSelected();

    bool nodeHasOptions(const mtps::size_type y) const noexcept;
    mtps::sptr<DiscreteTextComponent> optionsLabelAt(const mtps::size_type y) const;
    void setSelectedItem(const mtps::size_type index);
    void updateSelection();
    void setColorToLine(const mtps::size_type, const scene::Color &);
    mtps::vector<mtps::s32> optionsSelected() const;

protected:
    using ContainedElement = BaseClass::ContainedElement;

    MenuPaged *parentMenuPaged();
    const MenuPaged *parentMenuPaged() const;

    mtps::sptr<IFont> normalFont() const;
    Color normalColor() const;
    Color selectedColor() const;

    mtps::size_type m_previouslySelectedItem{0U};
    mtps::size_type m_selectedItem{0U};

    mtps::ireceiver m_receiver;

public:
    using BaseClass::BaseClass;
    ~MenuPage() override;

    void onCreated() override;
    void configure(mtps::vector<mtps::sptr<MenuPagedOption>> options,
        PageOptions page_options = PageOptions{});
    mtps::size_type SelectedOptionAtRow(const mtps::size_type row) const;

    mtps::emitter<const mtps::s32> Forward;
    mtps::emitter<mtps::vector<mtps::s32>> Accepted;
    mtps::emitter<> Back;
    mtps::emitter<mtps::vector<mtps::s32>> Canceled;
    mtps::emitter<const mtps::size_type, const mtps::s32> Selection;
};

} // namespace haf::scene

#endif
