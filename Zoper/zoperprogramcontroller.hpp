#ifndef __LIB_ZOPERPROGRAMCONTROLLER_HPP__
#define __LIB_ZOPERPROGRAMCONTROLLER_HPP__

#include "lib/core/programcontroller.hpp"
#include "lib/configuration.hpp"

namespace zoper
{
	class ZoperProgramController : public lib::core::ProgramController, public lib::Configuration
	{
	public:
		ZoperProgramController();
		virtual ~ZoperProgramController();
		
		// Inherited via ProgramController
		void onInit() override;
		virtual std::vector<lib::sptr<lib::scn::Scene>> scenesVector() override;
		virtual std::string resourceFile() override;
		virtual const lib::core::WindowCreationParams getWindowCreationParams() override;

	};
}

#endif
