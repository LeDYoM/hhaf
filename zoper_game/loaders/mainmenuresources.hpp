#pragma once

#ifndef ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP
#define ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP

#include <haf/resources/include/iresourceloader.hpp>

namespace zoper
{
class MainMenuResources : public haf::IResourceLoader
{
public:
    constexpr static char LogoId[] = "game_menu.logo";
    constexpr static char MenuFontId[] = "menu.mainFont";
    constexpr static char Shader[] = "menu.shader";

#ifdef TEST_BMP_FONT
    constexpr static char TestFontId[] = "menu.testFont";
#endif

    void loadResources(haf::IResourceHandler &) override;
};
} // namespace zoper

#endif