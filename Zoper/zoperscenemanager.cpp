#include "zoperscenemanager.hpp"
#include "menuscene.hpp"

namespace zoper
{
	ZoperSceneManager::ZoperSceneManager()
	{
		addScene(std::shared_ptr<MenuScene>(new MenuScene()));
	}

	ZoperSceneManager::~ZoperSceneManager()
	{
	}
}
