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
    : m_private{muptr<AnimationComponentPrivate>()} {}

void AnimationComponent::addAnimation(uptr<IAnimation> nanimation)
{
    m_private->m_animations.push_back(std::move(nanimation));
}

void AnimationComponent::update()
{
    m_private->m_animations.performUpdate([this](auto &animation) {
        if (!animation->animate())
        {
            animation->executeEndAction();
            m_private->m_animations.erase_value(animation);
        }
    });
}
} // namespace lib::scene
