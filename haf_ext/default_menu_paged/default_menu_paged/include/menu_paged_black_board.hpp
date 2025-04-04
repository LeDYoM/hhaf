#ifndef HAF_EXT_DEFAULT_MENU_MENUPAGED_BLACK_BOARD_COMPONENT_INCLUDE_HPP
#define HAF_EXT_DEFAULT_MENU_MENUPAGED_BLACK_BOARD_COMPONENT_INCLUDE_HPP

#include <haf/include/component/component.hpp>

namespace haf::exts::dmp
{
class MenuPagedBlackBoard : public component::Component
{
public:
    prop::PropertyState<htps::sptr<res::IFont>> NormalTextFont;
    prop::PropertyState<scene::Color> NormalColor;
    prop::PropertyState<scene::Color> SelectedColor;
    prop::PropertyState<bool> FinishSceneAtEnd;
};
}  // namespace haf::exts::dmp

#endif
