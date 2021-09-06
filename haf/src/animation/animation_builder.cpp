#include <haf/include/animation/animation_builder.hpp>
#include <haf/include/animation/animationcomponent.hpp>

using namespace htps;

namespace haf::anim
{
AnimationBuilder& AnimationBuilder::duration(time::TimePoint _duration)
{
    data_.duration_ = std::move(_duration);
    return *this;
}

AnimationBuilder& AnimationBuilder::endAction(ActionFunc _end_action)
{
    data_.end_action_ = std::move(_end_action);
    return *this;
}

AnimationBuilder& AnimationBuilder::animationDirection(
    AnimationDirection _animation_direction)
{
    data_.animation_direction_ = std::move(_animation_direction);
    return *this;
}

AnimationBuilder& AnimationBuilder::timer(htps::uptr<time::Timer> timer)
{
    data_.timer_ = std::move(timer);
    return *this;
}

AnimationData AnimationBuilder::extractData() noexcept
{
    return std::move(data_);
}

void AnimationBuilder::setData(AnimationData&& animation_data) noexcept
{
    data_ = std::move(animation_data);
}

AnimationBuilder& AnimationBuilder::times(htps::u32 times)
{
    if (times > static_cast<decltype(times)>(
                    std::numeric_limits<decltype(data_.times_)>::max()))
    {
        return continuous();
    }
    data_.times_ = static_cast<decltype(data_.times_)>(times);

    return *this;
}

AnimationBuilder& AnimationBuilder::continuous()
{
    data_.times_ = -1;
    return *this;
}

AnimationBuilder& AnimationBuilder::switchAnimation(bool const value)
{
    data_.switch_ = value;
    return *this;
}

}  // namespace haf::anim
