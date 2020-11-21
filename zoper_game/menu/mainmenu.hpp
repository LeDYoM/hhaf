#pragma once

#ifndef ZOPER_MAINMENU_INCLUDE_HPP
#define ZOPER_MAINMENU_INCLUDE_HPP

#include <menu_paged/include/menu_paged.hpp>

namespace zoper
{
using namespace haf;

class MainMenu : public haf::scene::MenuPaged
{
public:
    using BaseClass = haf::scene::MenuPaged;
    using BaseClass::prop;

    static constexpr char ClassName[] = "MainMenu";
    using BaseClass::BaseClass;

    virtual void onCreated() override;
};
} // namespace zoper

#endif