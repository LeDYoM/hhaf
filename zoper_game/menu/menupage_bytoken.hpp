#pragma once

#ifndef ZOPER_MENU_MENUPAGE_BYTOKEN_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_BYTOKEN_INCLUDE_HPP__

#include "menupage_bybase.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>

namespace zoper
{
	class MenuPageByToken : public MenuPageByBase
	{
	public:
        using BaseClass = MenuPageByBase;

		MenuPageByToken(lib::scene::SceneNode *parent, str name)
            : BaseClass(parent, name) {
            setType(GameMode::Token);
        }

        virtual ~MenuPageByToken() = default;
	};
}

#endif
