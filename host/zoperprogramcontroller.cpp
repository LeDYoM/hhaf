#include "zoperprogramcontroller.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"
#include "common.hpp"

namespace zoper
{
	ZoperProgramController::ZoperProgramController()
	{
	}

	ZoperProgramController::~ZoperProgramController()
	{
//		saveConfig();
	}
		
	void ZoperProgramController::onInit()
	{
	}

	const lib::IAppDescriptor ZoperProgramController::getAppDescriptor() const
	{
		return lib::IAppDescriptor
		{
			"Zoper",
			1,
			1,
			1,
			"config.cfg",
			"res.cfg",
			lib::WindowCreationParams
			(
				std::string("ZOPER"),
				(lib::u32)1024,
				(lib::u32)768,
				(lib::u32)32,
				(lib::u32)0,
				false,
				false,
				false
				)
		};
	}

//	void ZoperProgramController::start()
//	{
//		throw std::logic_error("The method or operation is not implemented.");
//	}

	int ZoperProgramController::loop()
	{
//		throw std::logic_error("The method or operation is not implemented.");
		return 0;
	}

	lib::ServicesRequest ZoperProgramController::getServicesRequest() const
	{
		return lib::ServicesRequest();
	}

	lib::VecSPtr<lib::scn::Scene> ZoperProgramController::scenesVector()
	{
		return{ lib::sptr<lib::scn::Scene>(new MenuScene), lib::sptr<lib::scn::Scene>(new GameScene) };
	}


}
