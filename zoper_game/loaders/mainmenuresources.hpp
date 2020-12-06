#ifndef ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP
#define ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP

namespace zoper
{
class MainMenuResources
{
public:
    constexpr static char LogoId[]     = "logo";
    constexpr static char MenuFontId[] = "menu_main_font";
    constexpr static char Shader[]     = "menu.shader";

#ifdef TEST_BMP_FONT
    constexpr static char TestFontId[] = "menu.testFont";
#endif
};
}  // namespace zoper

#endif