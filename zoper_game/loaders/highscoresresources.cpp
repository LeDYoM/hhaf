#include "highscoresresources.hpp"

#include <haf/resources/include/iresourcehandler.hpp>
#include <haf/resources/include/itexture.hpp>

namespace zoper
{

void HighScoresResources::loadResources(
    haf::res::IResourceHandler& resourceHandler)
{
    constexpr static char MenuFontFile[] = "resources/oldct.ttf";

    resourceHandler.loadTTFont(MenuFontId, MenuFontFile);
}
}  // namespace zoper
