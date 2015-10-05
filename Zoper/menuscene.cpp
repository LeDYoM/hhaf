#include "menuscene.hpp"

namespace zoper
{
	MenuScene::MenuScene()
		: Scene("MenuScene")
	{
	}


	MenuScene::~MenuScene()
	{
	}

	void MenuScene::onEnterScene()
	{
		Scene::onEnterScene();
		setNextScene("GameScene");
	}

	void MenuScene::onExitScene()
	{
		Scene::onExitScene();
	}

}
