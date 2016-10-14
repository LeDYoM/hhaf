#include "hostcontroller.hpp"
#include "window.hpp"
#include "log.hpp"
#include "appcontroller.hpp"
#include <SFML/Config.hpp>

namespace lib
{
	namespace core
	{
		namespace
		{
			std::vector<std::string> transformParams(int argc, char *argv[])
			{
				std::vector<std::string> temp;

				for (int i = 1; i<argc; ++i)
				{
					temp.push_back(argv[i]);
				}
				return temp;
			}
		}

		HostController::HostController(int argc, char *argv[])
			: Configuration{ "host.cfg" }
		{
			LOG_CONSTRUCT_NOPARAMS;
			LOG_INFO("Starting HostController...");
			LOG_INFO("Using SFML version " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << " as backend");
			LOG_INFO("Parsing parameters...");
			m_params = std::move(transformParams(argc,argv));
		}

		HostController::~HostController()
		{
			LOG_DESTRUCT_NOPARAMS;
			m_window.reset();
			m_params.clear();
		}

		int HostController::run()
		{
			while (!exit) {
				bool terminated{ m_app->update() };
				if (terminated) {
					m_app.reset();
				}

				exit = (m_app == nullptr);
			}

			if (!m_app) {
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