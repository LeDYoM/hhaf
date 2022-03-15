#ifndef HAF_EXT_MENUPAGED_MENUPAGED_PROPERTIES_INCLUDE_HPP
#define HAF_EXT_MENUPAGED_MENUPAGED_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/types/property_group.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::scene
{
struct NormalTextFont : PropertyStateBase<types::sptr<res::IFont>> {};

struct NormalColor : PropertyStateBase<Color> {};

struct SelectedColor : PropertyStateBase<Color> {};

struct FinishSceneAtEnd : PropertyStateBase<bool> {};

using MenuPagedProperties = types::PropertyGroup<NormalTextFont,
                                                NormalColor,
                                                SelectedColor,
                                                FinishSceneAtEnd>;

}  // namespace haf::scene

#endif
