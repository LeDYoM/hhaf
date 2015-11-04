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

	void MenuScene::onInit()
	{
	}

	void MenuScene::onDeinit()
	{
	}

	void MenuScene::onEnterScene()
	{
		setNextScene("GameScene");
	}

	void MenuScene::onExitScene()
	{
	}

	void MenuScene::update()
	{

	}
}
