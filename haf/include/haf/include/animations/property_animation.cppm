export module haf:animations:property_animation;

import :animation;
import :property_animation_data;
import :core:types;
import :core:log;

namespace haf::anim
{
/**
 * @brief Class representing an animation of a property. It uses functionality
 * from @b Animation to do that.
 */
class PropertyAnimation : public Animation
{
    using BaseClass = Animation;

public:
    /**
     * @brief Construct a new PropertyAnimation object
     *
     * @param animation_data Data for the animation
     * @param property_animation_data Data for the property animation
     */
    explicit PropertyAnimation(
        PropertyAnimationData&& property_animation_data) :
        BaseClass{core::move(property_animation_data)},
        m_data{core::move(property_animation_data)}
    {}

    bool animate() override
    {
        // Get result from parent
        const bool bResult{BaseClass::animate()};
        *(m_data_.delta_property) = delta();

        // Return result of base animation
        return bResult;
    }

private:
    PropertyAnimationData m_data;
};
}  // namespace haf::anim

#endif
