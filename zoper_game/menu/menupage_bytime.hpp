#pragma once

#ifndef ZOPER_MENU_MENUPAGE_BYTIME_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_BYTIME_INCLUDE_HPP__

#include "menupage_bybase.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>

namespace zoper
{
	class MenuPageByTime : public MenuPageByBase
	{
	public:
		using BaseClass = MenuPageByBase;

        MenuPageByTime(lib::scene::SceneNode *parent, str name)
            : BaseClass(parent, name) {
            setType(GameMode::Time);
        }

        virtual ~MenuPageByTime() = default;

	};
}

#endif
