#include "menupage_main.hpp"
#include "menupage.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>

namespace zoper
{
	MenuPageMain::MenuPageMain(lib::scene::SceneNode *parent, str name) : MenuPage{ parent, std::move(name) } {}

	MenuPageMain::~MenuPageMain() = default;

	void MenuPageMain::create()
	{
		BaseClass::create();

		addLabel("Play token mode");
		addLabel("Play time mode");
		addLabel("Options");
		addLabel("Exit");

		update();
	}

}