#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "core/scene.hpp"

namespace zoper
{
	class MenuScene : public lib::core::Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene();

		virtual void onActivated() override;
		virtual void onDeactivated() override;

	};
}

#endif
