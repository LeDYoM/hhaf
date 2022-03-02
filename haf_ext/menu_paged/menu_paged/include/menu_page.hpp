#ifndef HEF_EXT_MENU_PAGE_INCLUDE_HPP
#define HEF_EXT_MENU_PAGE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <menu_paged/include/menu_paged_option.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_nodes/scene_node_table.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

#include <htypes/include/connection.hpp>
#include <haf/include/scene_components/discretetextcomponent.hpp>

namespace haf::scene
{
class MenuPaged;
class MenuPage : public scene::nodes::TableNode<nodes::SceneNodeText>
{
private:
    using BaseClass = scene::nodes::TableNode<nodes::SceneNodeText>;
public:
    using BaseClass::BaseClass;
    ~MenuPage() override;

    void onCreated() override;
    void configure(htps::vector<htps::sptr<MenuPagedOption>> options,
                   PageOptions page_options = PageOptions{});
    htps::size_type SelectedOptionAtRow(const htps::size_type row) const;

    htps::emitter<const htps::s32> Forward;
    htps::emitter<htps::vector<htps::s32>> Accepted;
    htps::emitter<> Back;
    htps::emitter<htps::vector<htps::s32>> Canceled;
    htps::emitter<const htps::size_type, const htps::s32> Selection;
protected:
    using ContainedElement = BaseClass::ContainedElement;

    htps::rptr<MenuPaged const> parentMenuPaged() const;

    htps::sptr<res::IFont> normalFont() const;
    Color normalColor() const;
    Color selectedColor() const;

    htps::size_type previously_selected_item_{0U};
    htps::size_type selected_item_{0U};

private:
    void standarizeText(const htps::sptr<ContainedElement>& ntext);
    void goDown();
    void goUp();
    void goLeft();
    void goRight();
    void goSelected();

    bool nodeHasOptions(const htps::size_type y) const noexcept;
    htps::sptr<DiscreteTextComponent> optionsLabelAt(
        const htps::size_type y) const;
    void setSelectedItem(const htps::size_type index);
    void updateSelection();
    void setColorToLine(const htps::size_type, const scene::Color&);
    htps::vector<htps::s32> optionsSelected() const;
};

}  // namespace haf::scene

#endif
