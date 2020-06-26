#include "gameresources.hpp"

#include <haf/resources/include/iresourcehandler.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ittfont.hpp>

namespace zoper
{

constexpr char ScoreFontFile[] = "resources/score.ttf";

void GameResources::loadResources(haf::res::IResourceHandler &resourceHandler)
{
    resourceHandler.loadTTFont(ScoreFontId, ScoreFontFile);
}
} // namespace zoper
