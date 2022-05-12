#ifndef HAF_EXT_MENUPAGED_MENUPAGED_PROPERTIES_INCLUDE_HPP
#define HAF_EXT_MENUPAGED_MENUPAGED_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/property_group.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::scene
{
struct NormalTextFont : htps::PropertyStateBase<htps::sptr<res::IFont>>
{};

struct NormalColor : htps::PropertyStateBase<Color>
{};

struct SelectedColor : htps::PropertyStateBase<Color>
{};

struct FinishSceneAtEnd : htps::PropertyStateBase<bool>
{};

using MenuPagedProperties = htps::
    PropertyGroup<NormalTextFont, NormalColor, SelectedColor, FinishSceneAtEnd>;

}  // namespace haf::scene

#endif
