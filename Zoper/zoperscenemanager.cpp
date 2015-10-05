#include "zoperscenemanager.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"

namespace zoper
{
	ZoperSceneManager::ZoperSceneManager()
	{
		// Add scenes
		addScene(std::shared_ptr<MenuScene>(new MenuScene()));
		addScene(std::shared_ptr<GameScene>(new GameScene()));
	}

	ZoperSceneManager::~ZoperSceneManager()
	{
	}
}
