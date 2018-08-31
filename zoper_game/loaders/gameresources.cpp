#include "gameresources.hpp"
#include <lib/core/resourcemanager.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

    constexpr char ScoreFontFile[] = "resources/score.ttf";

	void GameResources::loadResources(core::ResourceManager&resourceManager)
	{
		resourceManager.loadResource<TTFont>(ScoreFontId, ScoreFontFile);
	}
}
