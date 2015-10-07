#include "gamescene.hpp"
#include "lib/board/boardmodel.hpp"
#include "lib/board/itilescontroller.hpp"

namespace zoper
{
	GameScene::GameScene()
		: Scene("GameScene")
	{
	}


	GameScene::~GameScene()
	{
	}

	void GameScene::onEnterScene()
	{
		Scene::onEnterScene();
		p_boardModel = lib::sptr<lib::board::BoardModel>(new lib::board::BoardModel(10,10));
	}

	void GameScene::onExitScene()
	{
		p_boardModel = nullptr;
		Scene::onExitScene();
	}

}
