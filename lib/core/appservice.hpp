#ifndef __LIB_APP_SERVICE_HPP__
#define __LIB_APP_SERVICE_HPP__

namespace lib
{
	namespace core
	{
		class Host;
	}

	class AppService
	{
	public:
		AppService(const AppService &rh) = delete;
		AppService &operator=(const AppService &rh) = delete;

		constexpr AppService() {};
		friend class Host;
	};
}
#endif
