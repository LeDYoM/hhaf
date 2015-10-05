#ifndef __GAMESCENE_HPP__
#define __GAMESCENE_HPP__

#include "lib/core/scene.hpp"

namespace zoper
{
	class GameScene : public lib::core::Scene
	{
	public:
		GameScene();
		virtual ~GameScene();

		virtual void onEnterScene() override;
		virtual void onExitScene() override;

	};
}

#endif
