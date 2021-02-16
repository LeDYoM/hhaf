#ifndef HAF_EXT_MENUPAGED_MENUPAGED_PROPERTIES_INCLUDE_HPP
#define HAF_EXT_MENUPAGED_MENUPAGED_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/grouping_property.hpp>
#include <haf/resources/include/ifont.hpp>
#include <haf/scene/include/color.hpp>

namespace haf::scene
{
struct NormalTextFont
{
    using value_type = mtps::sptr<haf::res::IFont>;
};

struct NormalColor
{
    using value_type = haf::scene::Color;
};

struct SelectedColor
{
    using value_type = haf::scene::Color;
};

struct SceneNodeSizeForPages
{
    using value_type = mtps::vector2df;
};

using MenuPagedProperties = mtps::PropertyGroup<NormalTextFont,
                                                NormalColor,
                                                SelectedColor,
                                                SceneNodeSizeForPages>;

}  // namespace haf::scene

#endif
