#include "gameresources.hpp"

#include <haf/resources/include/iresourcehandler.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ittfont.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;

constexpr char ScoreFontFile[] = "resources/score.ttf";

void GameResources::loadResources(IResourceHandler &resourceHandler)
{
    resourceHandler.loadTTFont(ScoreFontId, ScoreFontFile);
}
} // namespace zoper
