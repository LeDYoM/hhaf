#pragma once

#ifndef ZOPER_MENU_MENUPAGE_OPTIONS_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_OPTIONS_INCLUDE_HPP__

#include "menupage.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace zoper
{
	class MenuPageOptions : public MenuPage
	{
	public:
		using BaseClass = MenuPage;

		MenuPageOptions(lib::scene::SceneNode *parent, str name);
		virtual ~MenuPageOptions();

		void onCreated() override;
	};
}

#endif
