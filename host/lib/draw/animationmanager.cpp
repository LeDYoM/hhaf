#include "animationmanager.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace scn
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
					_animations.clear();
				}

				void AnimationManager::addAnimation(sptr<IAnimation> nanimation)
				{
					if (!_animations.empty())
					{
						auto elemFound = std::find_if(_animations.begin(), _animations.end(), [&nanimation](sptr<IAnimation> canimation)
						{
							return nanimation->node() == canimation->node() && canimation->animationType() == nanimation->animationType();
						});

						if (elemFound != _animations.end())
						{
							LOG_DEBUG("Same animation type already in node");
							removeFromspVector(*elemFound, _animations);
						}
					}

					_animations.push_back(nanimation);
					onAnimationStarted(nanimation, nanimation->node());
				}

				void AnimationManager::updateAnimations()
				{
					if (!_animations.empty())
					{
						for (auto &animation : _animations)
						{
							if (!animation->animate())
							{
								onAnimationFinished(animation, animation->node());
								_animationsToDelete.push_back(animation);
							}
						}

						if (!_animationsToDelete.empty())
						{
							for (auto animation : _animationsToDelete)
							{
								removeFromspVector(animation, _animations);
							}
							_animationsToDelete.clear();
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
}
