#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include <lib/gui/choosecontrolgroup.hpp>
#include <mtypes/include/types.hpp>
#include <lib/scene/nodes/nodequad.hpp>
#include <lib/scene/scene.hpp>

namespace zoper
{
	class MenuScene final : public lib::scene::Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene() = default;

		constexpr static lib::f32 MenuPosX = 165.0f;

		// Inherited via Scene
		virtual void onInit() override;
		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void updateScene() override;

	private:
		lib::sptr<lib::gui::ChooseControlGroup> m_chooseControlGroup;
		lib::sptr<lib::scene::nodes::NodeQuad> m_logo;
		lib::sptr<lib::scene::nodes::NodeQuad> m_background;
	};
}

#endif