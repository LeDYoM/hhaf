#include "menuscene.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/scn/resourcemanager.hpp"
#include "lib/scn/resource.hpp"

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
		_logo = createSprite("mainLogo");
		_logo->getAsSprite()->setTexture(*(resourceManager()->getResource("game_menu.logo")->getAsTexture()));

//		setNextScene("GameScene");
	}

	void MenuScene::onExitScene()
	{
	}

	void MenuScene::update()
	{

	}
}
