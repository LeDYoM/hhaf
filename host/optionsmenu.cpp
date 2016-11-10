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
			[this](u32 index, ChooseControl &self)
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
			},
			std::vector<sptr<OptionDescriptor>>{
				sptr<OptionDescriptor>(new OptionDescriptor("Antialiasing",
					true, 0, std::vector<std::string>{"Worst", "Bad", "Normal", "Good", "Best"})),
				sptr<OptionDescriptor>(new OptionDescriptor("Resolution",
					true, 0, std::vector<std::string>{"Worst", "1Bad", "2Normal", "3Good", "4Best"})),
				sptr<OptionDescriptor>(new OptionDescriptor("Fullscreen",
					true, 0, std::vector<std::string>{"No", "Yes"})),
				sptr<OptionDescriptor>(new OptionDescriptor("VSync",
					true, 0, std::vector<std::string>{"No", "Yes"})),
				sptr<OptionDescriptor>(new OptionDescriptor("Redefine keyboard")),
				sptr<OptionDescriptor>(new OptionDescriptor("Cancel")),
				sptr<OptionDescriptor>(new OptionDescriptor("Accept"))
			} ),
			lib::Configuration("config.cfg")
		{
		}

		OptionsMenu::~OptionsMenu() = default;

		void OptionsMenu::onAddedToScene()
		{
			setPosition(100, 700);
//			resetControl();
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
