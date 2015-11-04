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
		
		void onInit();

		// Inherited via ProgramController
		virtual std::vector<lib::sptr<lib::scn::Scene>> scenesVector() override;
	};
}

#endif
