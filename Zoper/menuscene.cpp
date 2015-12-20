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
		_logo = createSprite("mainLogo");
		auto _logoSprite = _logo->getAsSprite();
		_logoSprite->setTexture(*(resourceManager()->getResource("game_menu.logo")->getAsTexture()));
		auto a = _logoSprite->getLocalBounds();
		auto b = _logoSprite->getGlobalBounds();
		auto c = _logoSprite->getPosition();
	}

	void MenuScene::onDeinit()
	{

	}

	void MenuScene::onEnterScene()
	{
		_logo->setPositionX(getCoordinatesToCenter(_logo->getAsSprite()->getLocalBounds()).x);
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
