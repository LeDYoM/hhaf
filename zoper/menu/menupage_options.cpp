#include "menupage_options.hpp"
#include "menupage.hpp"
#include "menupagetype.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>

namespace zoper
{
	MenuPageOptions::MenuPageOptions(lib::scene::SceneNode *parent, str name) : MenuPage{ parent, std::move(name) } {}

	MenuPageOptions::~MenuPageOptions() = default;

	void MenuPageOptions::create()
	{
		BaseClass::create();
/*
		OptionModel("Antialiasing", { "Worst", "Bad", "Normal", "Good", "Best" }),
			OptionModel("Resolution", { "Worst", "Bad", "Normal", "Good", "Best" }),
			OptionModel("Fullscreen", { "No", "Yes" }),
			OptionModel("VSync", { "No", "Yes" }),
			OptionModel("Redefine keyboard"),
			OptionModel("Cancel", {}, OptionModelIndex{ 0 }),
			OptionModel("Accept", {}, OptionModelIndex{ 0 })
			*/
		configure(MenuPageMode::Optioner, 
		{ "Anti aliasing", "Resolution", "Fullscreen",  "VSync", "Redefine keyboard", "Cancel", "Accept" },
		{ 
			{ "Worst", "Bad", "Normal", "Good", "Best" },
			{ "Worst", "Bad", "Normal", "Good", "Best" },
			{ "No", "Yes" },
			{ "No", "Yes" }
		});

		Selection.connect([this](const size_type index) {
			switch (index) {
			// Cancel
			default:
			case 4:
				Back();
				break;
			case 5:
				Back();
				break;
			}
		});
	}
}
