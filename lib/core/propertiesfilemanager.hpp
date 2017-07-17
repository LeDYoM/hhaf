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
			sptr<T> create(const str &fileName) {
				auto result(msptr<T>());
				initialize(fileName, result.get());
				return result;
			}

			template <typename T>
			sptr<T> createInMemory() {
				auto result(msptr<T>());
				initialize(result.get());
				return result;
			}

		private:
			void initialize(const str &file, IUserProperties *source);
			void initialize(IUserProperties *source);
		};
	}
}

#endif
