#include <haf/include/animation/property_animation.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::anim
{
PropertyAnimation::PropertyAnimation(
    PropertyAnimationData&& property_animation_data) :
    BaseClass{htps::move(property_animation_data)},
    data_{htps::move(property_animation_data)}
{}

bool PropertyAnimation::animate()
{
    // Get result from parent
    const bool bResult{BaseClass::animate()};
    *(data_.delta_property) =  delta();

    // Return result of base animation
    return bResult;
}

}  // namespace haf::anim
