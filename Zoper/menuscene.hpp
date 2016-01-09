#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "keymapping.hpp"
#include "lib/menu/menumanager.hpp"
#include "lib/menu/menustep.hpp"
#include "lib/types.hpp"
#include <vector>

namespace zoper
{
	class MenuScene : public lib::menu::MenuManager, public KeyMapping
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
	private:
		lib::sptr<lib::scn::draw::Renderizable> _logo{ nullptr };
	};
}

#endif
