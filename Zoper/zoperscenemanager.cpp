#include "zoperscenemanager.hpp"
#include "menuscene.hpp"

namespace zoper
{
	ZoperSceneManager::ZoperSceneManager()
	{
		addScene(new MenuScene());
	}


	ZoperSceneManager::~ZoperSceneManager()
	{
	}
}
