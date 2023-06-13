HAF_PRAGMA_ONCE
#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/property_animation_data.hpp>

namespace haf::anim
{
/**
 * @brief Builder class to help the creation of animations.
 */
class PropertyAnimationBuilder
{
public:
    PropertyAnimationBuilder() = delete;

    /**
     * @brief Construct a new Property Animation Builder object
     * @param data An already created @b PropertyAnimationData
     */
    explicit PropertyAnimationBuilder(PropertyAnimationData data);

    PropertyAnimationBuilder(PropertyAnimationBuilder const&) = delete;
    PropertyAnimationBuilder& operator=(PropertyAnimationBuilder const&) =
        delete;
    PropertyAnimationBuilder(PropertyAnimationBuilder&&) noexcept = default;
    PropertyAnimationBuilder& operator=(PropertyAnimationBuilder&&) noexcept =
        default;

    PropertyAnimationBuilder& duration(time::TimePoint const& value);
    PropertyAnimationBuilder& times(htps::s32 value);
    PropertyAnimationBuilder& switchAnimation(bool value);
    PropertyAnimationBuilder& continuous();
    PropertyAnimationBuilder& actionWhenFinished(htps::function<void()> value);
    PropertyAnimationBuilder& deltaProperty(htps::uptr<IDeltaProperty> delta_p);
    PropertyAnimationData&& extract() noexcept;

private:
    PropertyAnimationData m_animation_data;
};

}  // namespace haf::anim

#endif
