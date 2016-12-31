#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "keymapping.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/include/types.hpp>
#include <vector>

namespace zoper
{
	class MenuScene final : public lib::menu::MenuManager, public KeyMapping
	{
	public:
		MenuScene();
		virtual ~MenuScene() = default;

		constexpr static lib::f32 MenuPosX = 165.0f;

		// Inherited via Scene
		virtual void onInit() override;
		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update() override;

		virtual lib::vector2df getDefaultSizeView() override;
	private:
		lib::sptr<lib::draw::NodeQuad> m_logo{ nullptr };
		lib::sptr<lib::draw::NodeQuad> m_background{ nullptr };
	};
}

#endif
