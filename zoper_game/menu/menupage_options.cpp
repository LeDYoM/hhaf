#include "menupage_options.hpp"
#include "menupage.hpp"
#include "menupagetype.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>

namespace zoper
{
	MenuPageOptions::MenuPageOptions(lib::scene::SceneNode *parent, str name) : MenuPage{ parent, std::move(name) } {}

	MenuPageOptions::~MenuPageOptions() = default;

	void MenuPageOptions::onCreated()
	{
		BaseClass::onCreated();
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
