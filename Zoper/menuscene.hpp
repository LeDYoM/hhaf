#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "lib/scn/scene.hpp"

namespace zoper
{
	class MenuScene : public lib::scn::Scene
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
		lib::sptr<lib::scn::draw::RenderGroup> _mainMenurg{ nullptr };
		lib::sptr<lib::scn::draw::Renderizable> _logo{ nullptr };
	};
}

#endif
