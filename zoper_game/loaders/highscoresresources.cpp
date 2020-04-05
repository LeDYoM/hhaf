#include "highscoresresources.hpp"

#include <lib/resources/include/iresourcehandler.hpp>

#include <lib/resources/include/itexture.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;

void HighScoresResources::loadResources(IResourceHandler &resourceHandler)
{
    constexpr static char MenuFontFile[] = "resources/oldct.ttf";

    resourceHandler.loadTTFont(MenuFontId, MenuFontFile);
}
} // namespace zoper
