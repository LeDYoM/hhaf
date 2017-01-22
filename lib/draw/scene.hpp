#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include "rendergroup.hpp"

#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <lib/core/timer.hpp>
#include <lib/core/events/event.hpp>
#include <lib/core/events/eventreceiver.hpp>
#include <lib/draw/animationcomponent.hpp>
#include <lib/draw/view.hpp>
#include <string>

namespace lib
{
	namespace core
	{
		class ResourceManager;
		class Host;
	}
	namespace draw
	{
		class RenderGroup;
		namespace anim
		{
			class IAnimation;
		}

		class Scene : public draw::RenderGroup, private anim::AnimationComponent
		{
		public:
			Scene(const std::string &_name);
			virtual ~Scene();

			virtual void onInit();
			virtual void onDeinit();
			virtual void onEnterScene();
			virtual void onExitScene();

			virtual void update() = 0;

			virtual vector2df getDefaultSizeView() = 0;
			vector2df getCoordinatesToCenter(const Rectf32 &coordinates) const;
			vector2df getCenterCoordinates() const;

			inline bool isActiveScene() const noexcept { return m_isActiveScene; }
			inline void addSubscription(sptr<events::EventSubscription> &&es) noexcept { eventConnector.addSubscription(std::move(es)); }
			void createAnimation(sptr<anim::IAnimation> nanimation, sptr<SceneNode> tracking = {}) noexcept { push_animation(std::move(nanimation), std::move(tracking)); }

		protected:

			void updateView();
			const uptr<View> &getView() const;
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }
			Timer clock;
			EventReceiver eventConnector;
			virtual Scene *const parentScene() noexcept override { return this; }

			inline void setAsActiveScene(const bool nv) noexcept { m_isActiveScene = nv; }

			uptr<draw::View> p_view;
			u32 _state;
			bool m_isActiveScene{ false };

			friend class lib::core::Host;
		};
	}
}

#endif
