#include "highscoresresources.hpp"

#include <lib/include/resources/iresourcehandler.hpp>

#include <lib/resources/texture.hpp>
#include <lib/resources/ttfont.hpp>

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
