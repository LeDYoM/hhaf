#ifndef __LIB_APP_SERVICE_HPP__
#define __LIB_APP_SERVICE_HPP__

namespace lib
{
	namespace core
	{
		class AppController;
	}

	class AppService
	{
	public:
		AppService(core::AppController *appController_) : appController{ appController_ } {}
		AppService &operator=(const AppService &rh) = delete;
		core::AppController *const appController;
	};
}
#endif
