#include "animationmanager.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			AnimationManager::AnimationManager()
			{
			}


			AnimationManager::~AnimationManager()
			{
				m_animations.clear();
			}

			void AnimationManager::addAnimation(sptr<IAnimation> nanimation)
			{
				if (!m_animations.empty())
				{
					auto elemFound = std::find_if(m_animations.begin(), m_animations.end(), [&nanimation](sptr<IAnimation> canimation)
					{
						return nanimation->node() == canimation->node() && canimation->animationType() == nanimation->animationType();
					});

					if (elemFound != m_animations.end())
					{
						logDebug("Same animation type already in node");
						removeFromspVector(m_animations, *elemFound);
					}
				}

				m_animations.push_back(nanimation);
				onAnimationStarted(nanimation, nanimation->node());
			}

			void AnimationManager::updateAnimations()
			{
				if (!m_animations.empty()) {
					for (auto &animation : m_animations) {
						if (!animation->animate()) {
							onAnimationFinished(animation, animation->node());
							m_animationsToDelete.push_back(animation);
						}
					}

					if (!m_animationsToDelete.empty()) {
						for (auto animation : m_animationsToDelete) {
							removeFromspVector(m_animations, animation);
						}
						m_animationsToDelete.clear();
					}
				}
			}

			void AnimationManager::onAnimationStarted(sptr<IAnimation> anim, sptr<Renderizable> node)
			{

			}

			void AnimationManager::onAnimationFinished(sptr<IAnimation> anim, sptr<Renderizable> node)
			{

			}

		}
	}
}
