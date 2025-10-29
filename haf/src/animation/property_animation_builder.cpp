#include <haf/include/animation/property_animation_builder.hpp>

using namespace haf::core;
using namespace haf::time;

namespace haf::anim
{
PropertyAnimationBuilder::PropertyAnimationBuilder(PropertyAnimationData data) :
    m_animation_data{core::move(data)}
{}

PropertyAnimationBuilder& PropertyAnimationBuilder::duration(
    TimePoint const& value)
{
    m_animation_data.Duration = value;
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::times(s32 const value)
{
    m_animation_data.Times = value;
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::switchAnimation(
    bool const value)
{
    m_animation_data.Switch = value;
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::continuous()
{
    return times(-1);
}

PropertyAnimationBuilder& PropertyAnimationBuilder::actionBeforeStarting(
    core::function<void()> value)
{
    m_animation_data.ActionBeforeStarting = core::move(value);
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::actionWhenFinished(
    function<void()> value)
{
    m_animation_data.ActionWhenFinished = core::move(value);
    return *this;
}

PropertyAnimationBuilder& PropertyAnimationBuilder::deltaProperty(
    uptr<IDeltaProperty> delta_p)
{
    m_animation_data.delta_property = core::move(delta_p);
    return *this;
}

PropertyAnimationData&& PropertyAnimationBuilder::extract() noexcept
{
    return core::move(m_animation_data);
}

}  // namespace haf::anim
