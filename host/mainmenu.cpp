#include "mainmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/menu/menudescriptors.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
#include <lib/core/host.hpp>
#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		MainMenu::MainMenu(lib::scn::draw::RenderGroup *parent)
			: lib::menu::IMenuControl{ "MainMenu", parent }, _gameConfig{ ":NextGame" }
		{
		}


		MainMenu::~MainMenu()
		{
		}

		void MainMenu::onCreate()
		{
			using namespace lib;
			using namespace lib::menu;

			auto callBack = [this](lib::u32 index, ChooseControl &self)
			{
				self;
				switch (index)
				{
				case 0:
					_gameConfig.addConfigInt(GameModeStr, 0, true);
					menuManager()->changeStep("StartLevelMenu");
					break;
				case 1:
					_gameConfig.addConfigInt(GameModeStr, 1, true);
					menuManager()->changeStep("StartLevelMenu");
					break;
				case 2:
					menuManager()->changeStep("OptionsMenu");
					break;
				case 3:
				default:
//					menuManager()->exitProgram();
					break;
				}
			};
			_chooseControl = sptr<ChooseControl>(new ChooseControl("mainmenu_chooseControl", parent(),
				lib::host().resourceManager().getResource("game_menu.mainFont"),
				sf::Color::Blue, sf::Color::Red,
				scn::draw::Alignment::Center,
				90, 1,
				callBack,
				sptr<CursorDescriptor>(new CursorDescriptor(3, vector2df{ 90.0f, 90.0f },sf::Color::Red)),
				std::vector<sptr<OptionDescriptor>>{
				sptr<OptionDescriptor>(new OptionDescriptor("Play token mode")),
				sptr<OptionDescriptor>(new OptionDescriptor("Play time mode")),
				sptr<OptionDescriptor>(new OptionDescriptor("Options")),
				sptr<OptionDescriptor>(new OptionDescriptor("Exit"))
			}));
			addChooseControl(_chooseControl);
			_chooseControl->setPosition(menuManager()->getCenterCoordinates().x, 700);
		}
	}
}
