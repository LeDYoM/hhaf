#ifndef __LIB_ANIMATIONMANAGER_HPP__
#define __LIB_ANIMATIONMANAGER_HPP__

#pragma once

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib
{
	namespace scene
	{
		namespace anim
		{
			class IAnimation;
			class AnimationComponent : public IComponent
			{
			public:
				AnimationComponent();
				~AnimationComponent();

				virtual void update() override;
				void addAnimation(uptr<IAnimation>);
			private:
				class AnimationComponentPrivate;
				AnimationComponentPrivate *m_private;
			};
		}
	}
}

#endif
