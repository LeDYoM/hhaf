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
		_mainMenurg = createNewRenderGroup("mainMenugroup");
		_logo = _mainMenurg->createSprite("mainLogo");
		auto _logoSprite = _logo->getAsSprite();
		_logoSprite->setTexture(*(resourceManager()->getResource("game_menu.logo")->getAsTexture()));
		_logo->setPositionX(getCoordinatesToCenter(_logo->getAsSprite()->getLocalBounds()).x);
		_mainMenurg->setVisible(false);
	}

	void MenuScene::onDeinit()
	{

	}

	void MenuScene::onEnterScene()
	{
		_mainMenurg->setVisible(true);
//		setNextScene("GameScene");
	}

	void MenuScene::onExitScene()
	{
	}

	void MenuScene::update()
	{

	}

	const lib::vector2df MenuScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}

}
