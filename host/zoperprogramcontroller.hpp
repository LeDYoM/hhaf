#ifndef __LIB_ZOPERPROGRAMCONTROLLER_HPP__
#define __LIB_ZOPERPROGRAMCONTROLLER_HPP__

#include <lib/include/iapp.hpp>

namespace zoper
{
	class ZoperProgramController : public lib::IApp
	{
	public:
		ZoperProgramController();
		virtual ~ZoperProgramController();
		
		// Inherited via ProgramController
		void onInit() override;
		virtual lib::VecSPtr<lib::scn::Scene> scenesVector() override;

		virtual const lib::IAppDescriptor getAppDescriptor() const override;

		//virtual void start() override;
		virtual int loop() override;

		virtual lib::ServicesRequest getServicesRequest() const override;

	};
}

#endif
