#include "zoperprogramcontroller.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"

namespace zoper
{
	ZoperProgramController::ZoperProgramController()
		: Configuration("config.cfg")
	{
	}

	ZoperProgramController::~ZoperProgramController()
	{
	}
		
	void ZoperProgramController::onInit()
	{
		// Init configuration data
		addConfigProperty("GraphicsLevel", "4");
		addConfigProperty("KeyLeft", std::to_string(sf::Keyboard::Left));
		addConfigProperty("KeyRight", std::to_string(sf::Keyboard::Right));
		addConfigProperty("KeyUp", std::to_string(sf::Keyboard::Up));
		addConfigProperty("KeyDown", std::to_string(sf::Keyboard::Down));
		addConfigProperty("KeyLaunch", std::to_string(sf::Keyboard::Space));
	}

	std::vector<lib::sptr<lib::scn::Scene>> ZoperProgramController::scenesVector()
	{
		return{ lib::sptr<lib::scn::Scene>(new MenuScene), lib::sptr<lib::scn::Scene>(new GameScene) };
	}
	std::string ZoperProgramController::resourceFile()
	{
		return "res.cfg";
	}
}
