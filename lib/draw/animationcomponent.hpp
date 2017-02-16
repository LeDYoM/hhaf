#ifndef __LIB_ANIMATIONMANAGER_HPP__
#define __LIB_ANIMATIONMANAGER_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/draw/icomponent.hpp>

namespace lib
{
	namespace draw
	{
		class SceneNode;
		namespace anim
		{
			class IAnimation;
			class AnimationComponent : public IComponent
			{
			public:
				AnimationComponent();
				~AnimationComponent();
			protected:
				void push_animation(sptr<IAnimation>, sptr <SceneNode> = {});

			};
		}
	}
}

#endif
