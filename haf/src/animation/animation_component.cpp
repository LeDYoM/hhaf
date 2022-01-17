#include <haf/include/animation/animation_component.hpp>
#include <hlog/include/hlog.hpp>
#include <htypes/include/lockablevector.hpp>

using namespace htps;

namespace haf::anim
{
class AnimationComponent::AnimationComponentPrivate
{
public:
    AnimationComponentPrivate() {}
    LockableVector<sptr<Animation>> animations_;
};

AnimationComponent::AnimationComponent() :
    p_{muptr<AnimationComponentPrivate>()}
{}

AnimationComponent::~AnimationComponent() = default;

void AnimationComponent::addAnimation(uptr<Animation> nanimation)
{
    p_->animations_.emplace_back(std::move(nanimation));
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
