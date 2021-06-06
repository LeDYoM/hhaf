#ifndef HAF_EXT_MENUPAGED_MENUPAGED_PROPERTIES_INCLUDE_HPP
#define HAF_EXT_MENUPAGED_MENUPAGED_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/grouping_property.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::scene
{
struct NormalTextFont
{
    using value_type = htps::sptr<haf::res::IFont>;
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
    using value_type = htps::vector2df;
};

using MenuPagedProperties = htps::PropertyGroup<NormalTextFont,
                                                NormalColor,
                                                SelectedColor,
                                                SceneNodeSizeForPages>;

}  // namespace haf::scene

#endif
