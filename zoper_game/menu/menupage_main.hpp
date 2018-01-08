#pragma once

#ifndef ZOPER_MENU_MENUPAGE_MAIN_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_MAIN_INCLUDE_HPP__

#include "menupage.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

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
