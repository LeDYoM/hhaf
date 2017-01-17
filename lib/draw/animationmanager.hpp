#ifndef __LIB_ANIMATIONMANAGER_HPP__
#define __LIB_ANIMATIONMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/core/events/eventreceiver.hpp>

namespace lib
{
	namespace draw
	{
		class SceneNode;
		namespace anim
		{
			class IAnimation;
			class AnimationManager
			{
			public:
				AnimationManager();
				~AnimationManager();
			protected:
				void push_animation(sptr<IAnimation>, sptr <SceneNode> = {});
			private:
				EventReceiver m_eventConnector;
			};
		}
	}
}

#endif
