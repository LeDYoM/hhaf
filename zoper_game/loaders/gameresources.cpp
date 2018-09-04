#include "gameresources.hpp"

#include <lib/include/resources/iresourcehandler.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

    constexpr char ScoreFontFile[] = "resources/score.ttf";

	void GameResources::loadResources(IResourceHandler&resourceHandler)
	{
        resourceHandler.loadFont(ScoreFontId, ScoreFontFile);
	}
}
