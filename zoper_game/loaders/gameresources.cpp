#include "gameresources.hpp"

#include <lib/resources/include/iresourcehandler.hpp>
#include <lib/resources/include/texture.hpp>
#include <lib/resources/include/ttfont.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;

constexpr char ScoreFontFile[] = "resources/score.ttf";

void GameResources::loadResources(IResourceHandler &resourceHandler)
{
    resourceHandler.loadTTFont(ScoreFontId, ScoreFontFile);
}
} // namespace zoper
