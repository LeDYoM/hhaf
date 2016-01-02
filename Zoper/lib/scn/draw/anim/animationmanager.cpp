#include "animationmanager.hpp"
#include "../../../core/vutils.hpp"

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
					_animations.push_back(nanimation);
				}

				void AnimationManager::updateAnimations()
				{
					if (!_animations.empty())
					{
						for (auto &animation : _animations)
						{
							if (!animation->animate())
							{
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

			}
		}
	}
}
