#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "keymapping.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/include/types.hpp>
#include <vector>

namespace zoper
{
	class MenuScene : public lib::menu::MenuManager, public KeyMapping
	{
	public:
		MenuScene();
		virtual ~MenuScene();

		constexpr static lib::f32 MenuPosX = 165.0f;

		// Inherited via Scene
		virtual void onInit() override;
		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update() override;

		virtual const lib::vector2df getDefaultSizeView() override;
	private:
		lib::sptr<lib::draw::NodeShape> _logo{ nullptr };
		lib::sptr<lib::draw::NodeShape> _background{ nullptr };
	};
}

#endif
