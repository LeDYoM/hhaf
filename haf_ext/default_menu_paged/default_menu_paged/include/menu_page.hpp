#ifndef HAF_EXT_DEFAULT_MENU_PAGE_INCLUDE_HPP
#define HAF_EXT_DEFAULT_MENU_PAGE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/core/properties.hpp>
#include <default_menu_paged/include/menu_paged_option.hpp>
#include <haf/include/scene_components/table_of_text.hpp>

#include <haf/include/events/connection.hpp>
#include <haf/include/scene_components/discrete_text_component.hpp>

namespace haf::exts::dmp
{
class MenuPage : public scene::TableOfText
{
private:
    using Base = scene::TableOfText;

public:
    using Base::Base;

    void onAttached() override;
    void update() override;

    prop::PropertyState<htps::vector<htps::sptr<MenuPagedOption>>> menu_options;
    prop::PropertyState<PageOptions> menu_page_options;

    htps::size_type SelectedOptionAtRow(const htps::size_type row) const;

    evt::emitter<const htps::s32> Forward;
    evt::emitter<htps::vector<htps::s32>> Accepted;
    evt::emitter<> Back;
    evt::emitter<htps::vector<htps::s32>> Canceled;
    evt::emitter<const htps::size_type, const htps::s32> Selection;

protected:
    htps::sptr<res::IFont> normalFont() const;
    scene::Color normalColor() const;
    scene::Color selectedColor() const;

    htps::size_type previously_selected_item_{0U};
    htps::size_type selected_item_{0U};

private:
    void onAllTableElementsCreated(fmath::vector2dst const) override;
    void standarizeText(const htps::sptr<ContainedElement>& ntext);
    void goDown();
    void goUp();
    void goLeft();
    void goRight();
    void goSelected();

    bool nodeHasOptions(const htps::size_type y) const noexcept;
    htps::sptr<scene::DiscreteTextComponent> optionsLabelAt(
        const htps::size_type y) const;
    void setSelectedItem(const htps::size_type index);
    void updateSelection();
    void setColorToLine(const htps::size_type, const scene::Color&);
    htps::vector<htps::s32> optionsSelected() const;
};

}  // namespace haf::exts::dmp

#endif
