#ifndef __GAMESCENE_HPP__
#define __GAMESCENE_HPP__

#include "lib/core/scene.hpp"
#include "lib/types.hpp"

namespace lib
{
	namespace board
	{
		class BoardModel;
	}
}
namespace zoper
{
	class GameScene : public lib::core::Scene
	{
	public:
		GameScene();
		virtual ~GameScene();

		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update();

	private:
		lib::sptr<lib::board::BoardModel> p_boardModel{ nullptr };
	};
}

#endif
