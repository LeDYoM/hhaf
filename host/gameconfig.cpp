#include "gameconfig.hpp"

namespace zoper
{
	GameConfig::GameConfig() : lib::IUserProperties(":GameConfig") {}
	GameConfig::~GameConfig() = default;

	void GameConfig::setProperties(lib::Configuration &config)
	{
		using namespace lib;

		gameMode = config.registerProperty("GameMode", 0);
		startLevel = config.registerProperty("StartLevel", 0u);
		score = config.registerProperty("Score", 0u);

	}

}