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

		Rectf32 r(rectFromSize(scenePerspective().size()));
		r.setLeftTop({ 0,750 });
		r.setSize({ 2000,4*150 });
		setMainLabels({ "Play token mode","Play time mode", "Options", "Exit" },r);
	}

}
