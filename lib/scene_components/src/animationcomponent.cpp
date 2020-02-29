#include "animationcomponent.hpp"

#include <lib/include/liblog.hpp>

#include <mtypes/include/lockablevector.hpp>

namespace lib::scene
{
class AnimationComponent::AnimationComponentPrivate
{
public:
    AnimationComponentPrivate() {}
    LockableVector<sptr<IAnimation>> m_animations;
};
AnimationComponent::AnimationComponent()
    : p_{muptr<AnimationComponentPrivate>()} {}

void AnimationComponent::addAnimation(uptr<IAnimation> nanimation)
{
    p_->m_animations.emplace_back(std::move(nanimation));
}

void AnimationComponent::update()
{
    p_->m_animations.performUpdate([this](auto &animation) {
        if (!animation->animate())
        {
            animation->executeEndAction();
            p_->m_animations.erase_value(animation);
        }
    });
}
} // namespace lib::scene
