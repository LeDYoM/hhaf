#include <haf/include/animation/animation_component.hpp>
#include <hlog/include/hlog.hpp>
#include <htypes/include/lockable_vector.hpp>

using namespace htps;

namespace haf::anim
{
class AnimationComponent::AnimationComponentPrivate
{
public:
    AnimationComponentPrivate() {}
    LockableVector<sptr<Animation>> animations_;

    void addAnimation(PropertyAnimationData&& data)
    {
        addAnimation(htps::muptr<PropertyAnimation>(htps::move(data)));
    }

    void addAnimation(uptr<Animation> nanimation)
    {
        animations_.emplace_back(htps::move(nanimation));
    }
};

AnimationComponent::AnimationComponent() :
    p_{muptr<AnimationComponentPrivate>()}
{}

AnimationComponent::~AnimationComponent() = default;

void AnimationComponent::addAnimation(PropertyAnimationBuilder&& builder)
{
    p_->addAnimation(builder.extract());
}

PropertyAnimationData AnimationComponent::make_property_animation_data()
{
    PropertyAnimationData property_animation_data{};
    property_animation_data.TimerProperty =
        attachedNode()->component<time::TimerComponent>()->addFreeTimer();
    property_animation_data.Times = 1;
    return property_animation_data;
}

PropertyAnimationBuilder AnimationComponent::make_property_animation_builder()
{
    return PropertyAnimationBuilder{make_property_animation_data()};
}

void AnimationComponent::update()
{
    p_->animations_.performUpdate([this](auto& animation) {
        if (!animation->animate())
        {
            animation->executeEndAction();
            p_->animations_.erase_value(animation);
        }
    });
}
}  // namespace haf::anim
