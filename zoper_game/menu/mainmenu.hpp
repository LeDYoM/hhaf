#pragma once

#ifndef ZOPER_MAINMENU_INCLUDE_HPP
#define ZOPER_MAINMENU_INCLUDE_HPP

#include <menu_paged/include/menu_paged.hpp>

namespace zoper
{
using namespace lib;

class MainMenu : public lib::scene::MenuPaged
{
public:
    using BaseClass = lib::scene::MenuPaged;

    static constexpr char ClassName[] = "MainMenu";
    MainMenu(scene::SceneNode *parent, mtps::str name);
    ~MainMenu() override;

    virtual void onCreated() override;
};
} // namespace zoper

#endif