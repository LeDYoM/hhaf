#ifndef __LIB_ANIMATIONMANAGER_HPP__
#define __LIB_ANIMATIONMANAGER_HPP__

#include <vector>
#include "ianimation.hpp"
#include <lib/include/types.hpp>
#include <lib/core/events/eventreceiver.hpp>

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
				~AnimationManager();
				void addAnimation(sptr<IAnimation> nanimation);
				void updateAnimations();
			private:
				EventReceiver m_eventConnector;
				vector_shared_pointers<IAnimation> m_animations;
				vector_shared_pointers<IAnimation> m_animationsToDelete;
			};
		}
	}
}

#endif
