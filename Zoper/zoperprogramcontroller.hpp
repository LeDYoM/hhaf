#ifndef __LIB_ZOPERPROGRAMCONTROLLER_HPP__
#define __LIB_ZOPERPROGRAMCONTROLLER_HPP__

#include "core/programcontroller.hpp"

namespace zoper
{
	class ZoperProgramController : public lib::core::ProgramController
	{
	public:
		ZoperProgramController();
		virtual ~ZoperProgramController();
		
		void onInit();
	};
}

#endif
