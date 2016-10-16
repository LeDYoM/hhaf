#ifndef __LIB_HOSTCONTROLLER_HPP__
#define __LIB_HOSTCONTROLLER_HPP__

#include <lib/core/vecsptr.hpp>
#include "configuration.hpp"
#include <lib/include/iapp.hpp>
#include <queue>
#include <string>


namespace lib
{
	namespace core
	{
		class Window;
		class AppController;

		class HostController : public Configuration
		{
		public:
			HostController(int argc, char *argv[]);
			virtual ~HostController();

			int run();

			void setApp(uptr<IApp> iapp);

		private:
			sptr<Window> m_window{ nullptr };
			uptr<AppController> m_app;
			bool exit{ false };
			std::vector<std::string> m_params;
		};
	}
}
#endif
