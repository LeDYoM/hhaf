#include "gameresources.hpp"
#include <mtypes/include/str.hpp>

namespace zoper
{
	using namespace lib;

	static const str resources_directory("resources/");
	static const str scoreFontPath(resources_directory + "score.ttf");

	void GameResourcesLoader::registerResources(core::ResourceLoader &resourceLoader)
	{
		resourceLoader.addToLoadList(scoreFontPath);
	}

	void GameResourcesLoader::aquireResources(core::ResourceLoader & resourceLoader)
	{
		m_scoreFont = resourceLoader.
	}
}
