#include "optionsmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/menu/menudescriptors.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>

#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		OptionsMenu::OptionsMenu()
			: lib::menu::MenuStep{ "OptionsMenu" }, lib::Configuration("config.cfg")
		{
		}


		OptionsMenu::~OptionsMenu()
		{
		}

		void OptionsMenu::onCreate()
		{
			// Read available resolutions
			std::vector<std::string> _resolutionsStr;
			for (const auto resolution : sf::VideoMode::getFullscreenModes())
			{
				_resolutionsStr.push_back(std::to_string(resolution.width) + "x" + std::to_string(resolution.height) + "x" + std::to_string(resolution.bitsPerPixel));
			}
			auto callBack = [this](lib::u32 index, lib::menu::ChooseControl &self)
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
					resetControl();
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
					resetControl();
					menuManager()->changeStep("MainMenu");
					break;
				}
			};

			_chooseControl = lib::sptr<lib::menu::ChooseControl>(new lib::menu::ChooseControl("optionsmenu_chooseControl",
				menuManager()->resourceManager()->getResource("game_menu.mainFont"),
				sf::Color::Blue, sf::Color::Red,
				lib::scn::draw::Alignment::Left,
				70, 1,
				callBack,
				lib::sptr<lib::menu::CursorDescriptor>(new lib::menu::CursorDescriptor(3, lib::vector2df{ 70.0f, 70.0f }, sf::Color::Red)),
				std::vector<lib::sptr<lib::menu::OptionDescriptor>>{
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Antialiasing", 
					true, 0, std::vector<std::string>{"Worst", "Bad", "Normal", "Good", "Best"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Resolution",
					true, 0, _resolutionsStr)),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Fullscreen",
					true, 0, std::vector<std::string>{"No", "Yes"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("VSync",
					true, 0, std::vector<std::string>{"No", "Yes"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Redefine keyboard")),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Cancel")),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Accept"))
			}));
			addMenuControl(_chooseControl);
			_chooseControl->setPosition(100, 700);
			resetControl();
		}

		void OptionsMenu::resetControl()
		{
			sf::VideoMode vm;
			vm.width = getAsInt(ResolutionXStr, 1024);
			vm.height = getAsInt(ResolutionYStr, 768);
			vm.bitsPerPixel = getAsInt(BPPStr, 32);
			lib::u32 index{ 0 };
			auto _resolutions( sf::VideoMode::getFullscreenModes() );
			for (lib::u32 i = 0u; i < _resolutions.size(); ++i)
			{
				if (_resolutions[i] == vm)
				{
					index = i;
				}
			}

			_chooseControl->setSelectedSubLabel(0, getAsInt(GraphicsLevelStr, 0));
			_chooseControl->setSelectedSubLabel(1, index);
			_chooseControl->setSelectedSubLabel(2, getAsInt(FulscreenStr, 0));
			_chooseControl->setSelectedSubLabel(3, getAsInt(VSyncStr, 0));
		}
	}
}
