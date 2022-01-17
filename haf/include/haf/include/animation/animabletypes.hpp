#ifndef HAF_ANIM_ANIMABLETYPE_INCLUDE_HPP
#define HAF_ANIM_ANIMABLETYPE_INCLUDE_HPP

#include <haf/include/scene/color.hpp>

namespace haf::anim
{

template <typename PropertyType>
struct AnimableType
{
    using type = PropertyType;
};

template <>
struct AnimableType<scene::Color>
{
    using type = scene::ColorImp<htps::s16>;
};

}  // namespace haf::anim

#endif
