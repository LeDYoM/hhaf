#pragma once

#ifndef ZOPER_MENU_MENUPAGE_MAIN_INCLUDE_HPP
#define ZOPER_MENU_MENUPAGE_MAIN_INCLUDE_HPP

#include "menupage.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>

namespace zoper
{
	class MenuPageMain : public MenuPage
	{
	public:
		using BaseClass = MenuPage;

		MenuPageMain(lib::scene::SceneNode *parent, str name);
		virtual ~MenuPageMain();

		void onCreated() override;
	};
}

#endif
