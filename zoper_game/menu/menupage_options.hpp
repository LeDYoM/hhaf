#pragma once

#ifndef ZOPER_MENU_MENUPAGE_OPTIONS_INCLUDE_HPP
#define ZOPER_MENU_MENUPAGE_OPTIONS_INCLUDE_HPP

#include "menupage.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>

namespace zoper
{
class MenuPageOptions : public MenuPageOptioner
{
public:
    using BaseClass = MenuPageOptioner;

    MenuPageOptions(lib::scene::SceneNode *parent, str name);
    virtual ~MenuPageOptions();

    void onCreated() override;
};
} // namespace zoper

#endif
