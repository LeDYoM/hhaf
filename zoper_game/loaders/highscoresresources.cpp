#include "highscoresresources.hpp"

#include <haf/resources/include/iresourcehandler.hpp>

#include <haf/resources/include/itexture.hpp>

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
