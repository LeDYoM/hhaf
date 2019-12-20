#pragma once

#ifndef ZOPER_MENU_MENUPAGE_BYBASE_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_BYBASE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include "menupage.hpp"
#include "../gameshareddata.hpp"

namespace zoper
{
class MenuPageByBase : public MenuPage
{
public:
    using BaseClass = MenuPage;

    MenuPageByBase(lib::scene::SceneNode *parent, str name);
    virtual ~MenuPageByBase();

    void onCreated() override;

protected:
    constexpr void setType(const GameMode gameModePage) noexcept { m_gameModePage = gameModePage; }

private:
    GameMode m_gameModePage;
};
} // namespace zoper

#endif
