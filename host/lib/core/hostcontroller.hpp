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
		class HostTask;
		class AppController;

		class HostController : public Configuration
		{
		public:
			HostController(const std::vector<std::string> &params);
			virtual ~HostController();

			int run();

			void setApp(uptr<IApp> iapp);

		private:
			sptr<Window> m_window{ nullptr };
			bool exit{ false };
			uptr<AppController> m_app;
		};
	}
}
#endif
