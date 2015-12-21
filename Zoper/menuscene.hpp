#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "lib/menu/menumanager.hpp"

namespace zoper
{
	class MenuScene : public lib::menu::MenuManager
	{
	public:
		MenuScene();
		virtual ~MenuScene();

		// Inherited via Scene
		virtual void onInit() override;
		virtual void onDeinit() override;
		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update() override;

		virtual const lib::vector2df getDefaultSizeView() override;

	};
}

#endif
