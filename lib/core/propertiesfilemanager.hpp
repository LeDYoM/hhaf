#ifndef LIB_PROPERTIESFILEMANAGER_HPP__
#define LIB_PROPERTIESFILEMANAGER_HPP__

#include <mtypes/include/types.hpp>
#include "configuration.hpp"
#include "appservice.hpp"

namespace lib
{
	class IUserProperties;
	namespace core
	{
		class PropertiesFileManager : public AppService
		{
		public:
			PropertiesFileManager();
			virtual ~PropertiesFileManager();

			template <typename T>
			sptr<T> create() {
				auto result(msptr<T>());
				initialize(result.get());
				return result;
			}
		private:
			void initialize(IUserProperties *source);
		};
	}
}

#endif
