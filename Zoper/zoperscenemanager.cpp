#include "zoperscenemanager.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"

namespace zoper
{
	ZoperSceneManager::ZoperSceneManager()
	{
		// Add scenes
		addScene(lib::sptr<MenuScene>(new MenuScene()));
		addScene(lib::sptr<GameScene>(new GameScene()));
	}

	ZoperSceneManager::~ZoperSceneManager()
	{
	}
}
