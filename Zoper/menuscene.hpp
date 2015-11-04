#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "lib/scn/scene.hpp"

namespace zoper
{
	class MenuScene : public lib::scn::Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene();

		// Inherited via Scene
		virtual void onInit() override;
		virtual void onDeinit() override;
		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update();
	};
}

#endif
