#pragma once

#ifndef ZOPER_MENU_MENUPAGE_BYTOKEN_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_BYTOKEN_INCLUDE_HPP__

#include "menupage.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace zoper
{
	class MenuPageByToken : public MenuPage
	{
	public:
		using BaseClass = MenuPage;

		MenuPageByToken(lib::scene::SceneNode *parent, str name);
		virtual ~MenuPageByToken();

		void create() override;
	};
}

#endif
