export haf : animations : property_animation_builder;

import :property_animation_data;
import :core:types;

namespace haf::anim
{
/**
 * @brief Builder class to help the creation of animations.
 */
class PropertyAnimationBuilder
{
public:
    /**
     * @brief Construct a new Property Animation Builder object
     * @param data An already created @b PropertyAnimationData
     */
    explicit PropertyAnimationBuilder(PropertyAnimationData data) :
        m_animation_data{core::move(data)}
    {}

    PropertyAnimationBuilder(PropertyAnimationBuilder const&) = delete;
    PropertyAnimationBuilder& operator=(PropertyAnimationBuilder const&) =
        delete;
    PropertyAnimationBuilder(PropertyAnimationBuilder&&) noexcept = default;
    PropertyAnimationBuilder& operator=(PropertyAnimationBuilder&&) noexcept =
        default;

    PropertyAnimationBuilder& duration(TimePoint const& value)
    {
        m_animation_data.Duration = value;
        return *this;
    }

    PropertyAnimationBuilder& times(s32 value)
    {
        m_animation_data.Times = htps::move(value);
        return *this;
    }

    PropertyAnimationBuilder& switchAnimation(bool value)
    {
        m_animation_data.Switch = htps::move(value);
        return *this;
    }

    PropertyAnimationBuilder& continuous()
    {
        return times(-1);
    }

    PropertyAnimationBuilder& actionWhenFinished(
        function<void()> value)
    {
        m_animation_data.ActionWhenFinished = htps::move(value);
        return *this;
    }

    PropertyAnimationBuilder& deltaProperty(
        uptr<IDeltaProperty> delta_p)
    {
        m_animation_data.delta_property = htps::move(delta_p);
        return *this;
    }

    PropertyAnimationData&& extract() noexcept
    {
        return htps::move(m_animation_data);
    }

private:
    PropertyAnimationData m_animation_data;
};

}  // namespace haf::anim
