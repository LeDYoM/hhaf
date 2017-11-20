#include "menupage_bytoken.hpp"
#include "menupage.hpp"
#include "menupagetype.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>

namespace zoper
{
	MenuPageByToken::MenuPageByToken(lib::scene::SceneNode *parent, str name) : MenuPage{ parent, std::move(name) } {}

	MenuPageByToken::~MenuPageByToken() = default;

	void MenuPageByToken::create()
	{
		BaseClass::create();

		configure(MenuPageMode::Optioner, 
		{ "Start level token mode", "Play", "Back" }, { { "0","1","2", "3", "4", "5", "6", "7", "8", "9", "10" } });

		Selection.connect([this](const size_type index) {
			switch (index) {
			// Play
			case 1:
//				Forward(MenuPageType::SelectLevelToken);
				break;
			// Back
			case 2:
				Back();
				break;
			default:
				break;
			}
		});
	}
}