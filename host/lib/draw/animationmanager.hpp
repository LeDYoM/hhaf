#ifndef __LIB_ANIMATIONMANAGER_HPP__
#define __LIB_ANIMATIONMANAGER_HPP__

#include <vector>
#include "ianimation.hpp"
#include <lib/core/vecsptr.hpp>

namespace lib
{
	namespace draw
	{
		class Renderizable;
		namespace anim
		{
			class AnimationManager
			{
			public:
				AnimationManager();
				virtual ~AnimationManager();
				void addAnimation(sptr<IAnimation> nanimation);
				void updateAnimations();
				virtual void onAnimationStarted(sptr<IAnimation> anim, sptr<Renderizable> node);
				virtual void onAnimationFinished(sptr<IAnimation> anim, sptr<Renderizable> node);
			private:
				VecSPtr<IAnimation> _animations;
				std::vector<sptr<IAnimation>> _animationsToDelete;
			};
		}
	}
}

#endif
