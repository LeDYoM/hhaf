#include "gameresources.hpp"

#include <lib/resources_interface/include/iresourcehandler.hpp>
#include <lib/resources_interface/include/itexture.hpp>
#include <lib/resources_interface/include/ittfont.hpp>

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
