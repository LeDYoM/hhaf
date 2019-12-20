#pragma once

#ifndef ZOPER_MENU_MENUPAGE_BYBASE_INCLUDE_HPP
#define ZOPER_MENU_MENUPAGE_BYBASE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include "menupage.hpp"
#include "../gameshareddata.hpp"

namespace zoper
{
class MenuPageByBase : public MenuPageOptioner
{
public:
    using BaseClass = MenuPageOptioner;

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
