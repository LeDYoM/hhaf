#include "menuscene.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/scn/resourcemanager.hpp"
#include "lib/scn/resource.hpp"

#include "mainmenu.hpp"
#include "optionsmenu.hpp"

namespace zoper
{
	MenuScene::MenuScene()
		: lib::menu::MenuManager("MenuScene")
	{
	}


	MenuScene::~MenuScene()
	{
	}

	void MenuScene::onInit()
	{
		addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::MainMenu));
		addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::OptionsMenu));
	}

	void MenuScene::onDeinit()
	{

	}

	void MenuScene::onEnterScene()
	{
		start("MainMenu");
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
