#include "highscoresresources.hpp"

#include <lib/resources_interface/include/iresourcehandler.hpp>

#include <lib/resources_interface/include/itexture.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;

void HighScoresResources::loadResources(IResourceHandler &resourceHandler)
{
    constexpr static char MenuFontFile[] = "resources/oldct.ttf";

    resourceHandler.loadTTFont(MenuFontId, MenuFontFile);
}
} // namespace zoper
