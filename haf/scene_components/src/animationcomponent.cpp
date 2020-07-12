#include "animationcomponent.hpp"

#include <hlog/include/hlog.hpp>

#include <mtypes/include/lockablevector.hpp>

using namespace mtps;

namespace haf::scene
{
class AnimationComponent::AnimationComponentPrivate
{
public:
    AnimationComponentPrivate() {}
    LockableVector<sptr<Animation>> m_animations;
};

AnimationComponent::AnimationComponent() :
    p_{muptr<AnimationComponentPrivate>()}
{}

AnimationComponent::~AnimationComponent() = default;

void AnimationComponent::addAnimation(uptr<Animation> nanimation)
{
    p_->m_animations.emplace_back(std::move(nanimation));
}

void AnimationComponent::update()
{
    p_->m_animations.performUpdate([this](auto& animation) {
        if (!animation->animate())
        {
            animation->executeEndAction();
            p_->m_animations.erase_value(animation);
        }
    });
}
}  // namespace haf::scene
