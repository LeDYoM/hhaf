#include "optionsmenu.hpp"
#include "lib/menu/menumanager.hpp"
#include "lib/menu/choosecontrol.hpp"
#include "lib/menu/menudescriptors.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/scn/resourcemanager.hpp"
#include "lib/scn/resource.hpp"

#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		OptionsMenu::OptionsMenu()
			: lib::menu::MenuStep{ "OptionsMenu" }, lib::Configuration("config.cfg"), _gameConfig{ ":NextGame" }
		{
		}


		OptionsMenu::~OptionsMenu()
		{
		}

		void OptionsMenu::onCreate()
		{
			auto rManager = menuManager()->resourceManager();
			// Read available resolutions
			auto _resolutions = sf::VideoMode::getFullscreenModes();
			std::vector<std::string> _resolutionsStr;
			for (const auto resolution : _resolutions)
			{
				_resolutionsStr.push_back(std::to_string(resolution.width) + "x" + std::to_string(resolution.height) + "x" + std::to_string(resolution.bitsPerPixel));
			}
			auto callBack = [this](lib::u32 index, const lib::menu::ChooseControl &self)
			{
				switch (index)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					menuManager()->changeStep("KeyRedefinitionMenu");
					break;
				case 5:
					menuManager()->changeStep("MainMenu");
					reset();
					break;
				case 6:
				default:
					addConfigInt(GraphicsLevelStr, self.getSelectedSubLabel(0), true);
					auto _resolution = sf::VideoMode::getFullscreenModes()[self.getSelectedSubLabel(1)];
					if (_resolution.isValid())
					{
						addConfigInt(ResolutionXStr, _resolution.width, true);
						addConfigInt(ResolutionYStr, _resolution.height, true);
						addConfigInt(BPPStr, _resolution.bitsPerPixel, true);
					}
					addConfigInt(FulscreenStr, self.getSelectedSubLabel(2), true);
					addConfigInt(VSyncStr, self.getSelectedSubLabel(3), true);
					saveConfig();
					menuManager()->changeStep("MainMenu");
					break;
				}
			};
			_chooseControl = lib::sptr<lib::menu::ChooseControl>(new lib::menu::ChooseControl("optionsmenu_chooseControl",
				rManager->getResource("game_menu.mainFont"),
				lib::scn::draw::Alignment::Left,
				70, 1,
				callBack,
				lib::sptr<lib::menu::CursorDescriptor>(new lib::menu::CursorDescriptor(3, lib::vector2df{ 70.0f, 70.0f }, sf::Color::Red)),
				std::vector<lib::sptr<lib::menu::OptionDescriptor>>{
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Antialiasing", sf::Color::Blue
					,true,0,std::vector<std::string>{"Worst","Bad","Normal","Good","Best"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Resolution", sf::Color::Blue
						, true, 0, _resolutionsStr)),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Fullscreen", sf::Color::Blue
					, true, 0, std::vector<std::string>{"No", "Yes"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("VSync", sf::Color::Blue
						, true, 0, std::vector<std::string>{"No", "Yes"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Redefine keyboard", sf::Color::Blue)),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Cancel", sf::Color::Blue,true)),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Accept", sf::Color::Blue, true))
			}));
			addMenuControl(_chooseControl);
			_chooseControl->setPosition(100, 700);
		}
	}
}
