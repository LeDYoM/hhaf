#include "gameresources.hpp"

#include <lib/resources/include/iresourcehandler.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/include/ittfont.hpp>

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
