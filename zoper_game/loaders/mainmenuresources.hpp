#pragma once

#ifndef ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP
#define ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP

#include <lib/include/resources/iresourceloader.hpp>

namespace zoper
{
class MainMenuResources : public lib::IResourceLoader
{
public:
    constexpr static char LogoId[] = "game_menu.logo";
    constexpr static char MenuFontId[] = "menu.mainFont";
    constexpr static char Shader[] = "menu.shader";

#ifdef TEST_BMP_FONT
    constexpr static char TestFontId[] = "menu.testFont";
#endif

    void loadResources(lib::IResourceHandler &) override;
};
} // namespace zoper

#endif