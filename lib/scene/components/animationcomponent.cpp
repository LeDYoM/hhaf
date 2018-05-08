#include "animationcomponent.hpp"
#include <lib/scene/ianimation.hpp>

#include <mtypes/include/log.hpp>
#include <algorithm>

namespace lib
{
	namespace scene
	{
		namespace anim
		{
			class AnimationComponent::AnimationComponentPrivate
			{
			public:
				AnimationComponentPrivate() {}
				vector_shared_pointers<IAnimation> m_animations;
			};
			AnimationComponent::AnimationComponent()
				: m_private{ muptr<AnimationComponentPrivate> }
			{
			}

			AnimationComponent::~AnimationComponent() {}

			void AnimationComponent::addAnimation(uptr<IAnimation> nanimation)
			{
				m_private->m_animations.push_back(std::move(nanimation));
			}

			void AnimationComponent::update()
			{
				if (!m_private->m_animations.empty()) {
					bool animsFinished{ false };
					for (auto& animation : m_private->m_animations) {
						if (!animation->animate()) {
							animation = nullptr;
							animsFinished = true;
						}
					}

					if (animsFinished) {
						m_private->m_animations.remove_values(nullptr);
					}
				}
			}
		}
	}
}
