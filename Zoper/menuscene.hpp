#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "lib/core/scene.hpp"

namespace zoper
{
	class MenuScene : public lib::core::Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene();

		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update();
	};
}

#endif
