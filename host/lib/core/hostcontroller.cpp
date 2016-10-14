#include "hostcontroller.hpp"
#include "window.hpp"
#include "log.hpp"
#include "appcontroller.hpp"

namespace lib
{
	namespace core
	{

		HostController::HostController(const std::vector<std::string> &params)
			: Configuration{ "host.cfg" }
		{
			params;
			LOG_CONSTRUCT_NOPARAMS;
			LOG_INFO("Starting HostController...");
		}

		HostController::~HostController()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		int HostController::run()
		{
			while (!exit)
			{
				bool terminated{ m_app->update() };
				if (terminated) {
					m_app.reset();
				}

				exit = (m_app == nullptr);
			}

			if (!m_app)
			{
				LOG_INFO("App destroyed. Exiting normally");
			}
			return 0;
		}

		void HostController::setApp(uptr<IApp> iapp)
		{
			m_app = std::make_unique<AppController>(std::move(iapp));
		}
	}
}