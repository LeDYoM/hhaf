#include "optionsmenu.hpp"
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
		using namespace lib;
		using namespace lib::menu;

		OptionsMenu::OptionsMenu(MenuManager *parent)
			: ChooseControl( "OptionsMenu", parent,
			[this](u32 index)
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
					break;
				case 6:
				default:
					addConfigInt(GraphicsLevelStr, getSelectedSubLabel(0), true);
					auto _resolution = sf::VideoMode::getFullscreenModes()[getSelectedSubLabel(1)];
					if (_resolution.isValid())
					{
						addConfigInt(ResolutionXStr, _resolution.width, true);
						addConfigInt(ResolutionYStr, _resolution.height, true);
						addConfigInt(BPPStr, _resolution.bitsPerPixel, true);
					}
					addConfigInt(FulscreenStr, getSelectedSubLabel(2), true);
					addConfigInt(VSyncStr, getSelectedSubLabel(3), true);
					saveConfig();
					menuManager()->changeStep("MainMenu");
					break;
				}
			},
			std::vector<sptr<OptionDescriptor>>{
				msptr<OptionDescriptor>("Antialiasing",
					true, 0, std::vector<std::string>{"Worst", "Bad", "Normal", "Good", "Best"}),
				msptr<OptionDescriptor>("Resolution",
					true, 0, std::vector<std::string>{"Worst", "Bad", "Normal", "Good", "Best"}),
				msptr<OptionDescriptor>("Fullscreen",
					true, 0, std::vector<std::string>{"No", "Yes"}),
				msptr<OptionDescriptor>("VSync",
					true, 0, std::vector<std::string>{"No", "Yes"}),
				msptr<OptionDescriptor>("Redefine keyboard"),
				msptr<OptionDescriptor>("Cancel"),
				msptr<OptionDescriptor>("Accept")
			} ),
			lib::Configuration("config.cfg")
		{
		}

		OptionsMenu::~OptionsMenu() = default;

		void OptionsMenu::onAddedToScene()
		{
			setPosition(100, 700);
		}
	}
}
