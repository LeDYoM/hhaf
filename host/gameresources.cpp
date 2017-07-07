#include "gameresources.hpp"
#include <mtypes/include/str.hpp>

namespace zoper
{
	void GameResourcesLoader::loadResources(lib::core::ResourceLoader &resourceLoader)
	{
		using namespace lib;

		const str resources_directory("resources/");
		resourceLoader.addToLoadList(resources_directory + "score.ttf",m_scoreFont);
	}
}
