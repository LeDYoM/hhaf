#pragma once

#ifndef ZOPER_MENU_MENUPAGE_BYNAME_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_BYNAME_INCLUDE_HPP__

#include "menupage.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace zoper
{
	class MenuPageByTime : public MenuPage
	{
	public:
		using BaseClass = MenuPage;

		MenuPageByTime(lib::scene::SceneNode *parent, str name);
		virtual ~MenuPageByTime();

		void create() override;
	};
}

#endif
