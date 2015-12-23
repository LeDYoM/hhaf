#include "menuscene.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/scn/resourcemanager.hpp"
#include "lib/scn/resource.hpp"

#include "mainmenu.hpp"

namespace zoper
{
	MenuScene::MenuScene()
		: lib::menu::MenuManager("MenuScene")
	{
//		getSteps();

	}


	MenuScene::~MenuScene()
	{
	}

	void MenuScene::onInit()
	{
		addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::MainMenu));
	}

	void MenuScene::onDeinit()
	{

	}

	void MenuScene::onEnterScene()
	{
		start("MainMenu");
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
	/*
	int MenuScene::stepsVector()
	{
		return 0;
//		return{ lib::sptr<lib::menu::MenuStep>(new zoper::menu::MainMenu) };
	}

	void MenuScene::getSteps()
	{

	}
	*/
}
