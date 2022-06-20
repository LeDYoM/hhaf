#include <haf/include/animation/property_animation_builder.hpp>

using namespace htps;
using namespace haf::time;

namespace haf::anim
{
PropertyAnimationBuilder::PropertyAnimationBuilder(PropertyAnimationData data) :
    m_animation_data{htps::move(data)}
{}

PropertyAnimationBuilder& PropertyAnimationBuilder::duration(
    TimePoint const& value)
{
    m_animation_data.Duration = value;
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::times(s32 value)
{
    m_animation_data.Times = htps::move(value);
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::switchAnimation(bool value)
{
    m_animation_data.Switch = htps::move(value);
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::continuous()
{
    return times(-1);
}

PropertyAnimationBuilder& PropertyAnimationBuilder::actionWhenFinished(
    function<void()> value)
{
    m_animation_data.ActionWhenFinished = htps::move(value);
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::deltaProperty(
    uptr<IDeltaProperty> delta_p)
{
    m_animation_data.delta_property = htps::move(delta_p);
    return *this;
}

PropertyAnimationData&& PropertyAnimationBuilder::extract() noexcept
{
    return htps::move(m_animation_data);
}

}  // namespace haf::anim
