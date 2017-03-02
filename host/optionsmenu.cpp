#include "optionsmenu.hpp"
#include <lib/gui/ChooseControlGroup.hpp>
#include <lib/gui/choosecontrol.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include "common.hpp"
#include "menuscene.hpp"

namespace zoper
{
	namespace zmenu
	{
		using namespace lib;
		using namespace lib::gui;

		OptionsMenu::OptionsMenu(lib::draw::SceneNode *parent, lib::str_const &&name)
			: ChooseControl( parent, std::move(name)),
/*			[this](u32 index)
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
					chooseControlGroup()->changeStep("KeyRedefinitionMenu");
					break;
				case 5:
					chooseControlGroup()->changeStep("MainMenu");
					break;
				case 6:
				default:
					value(GraphicsLevelStr)->set(selectedSubLabel(0));
					auto resolution = sf::VideoMode::getFullscreenModes()[selectedSubLabel(1)];
					if (resolution.isValid())
					{
						value(ResolutionXStr)->set(resolution.width);
						value(ResolutionYStr)->set(resolution.height);
						value(BPPStr)->set(resolution.bitsPerPixel);
					}
					value(FulscreenStr)->set(selectedSubLabel(2));
					value(VSyncStr)->set(selectedSubLabel(3));
					saveConfig();
					chooseControlGroup()->changeStep("MainMenu");
					break;
				}
			},
			std::vector<sptr<OptionDescriptor>>{
				msptr<OptionDescriptor>("Antialiasing",
					std::vector<std::string>{"Worst", "Bad", "Normal", "Good", "Best"}),
				msptr<OptionDescriptor>("Resolution",
					std::vector<std::string>{"Worst", "Bad", "Normal", "Good", "Best"}),
				msptr<OptionDescriptor>("Fullscreen",
					std::vector<std::string>{"No", "Yes"}),
				msptr<OptionDescriptor>("VSync",
					std::vector<std::string>{"No", "Yes"}),
				msptr<OptionDescriptor>("Redefine keyboard"),
				msptr<OptionDescriptor>("Cancel"),
				msptr<OptionDescriptor>("Accept")
			} ),*/
			lib::Configuration("config.cfg")
		{
		}

		OptionsMenu::~OptionsMenu() = default;
	}
}
