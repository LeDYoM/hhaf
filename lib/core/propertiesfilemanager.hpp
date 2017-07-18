#ifndef LIB_PROPERTIESFILEMANAGER_HPP__
#define LIB_PROPERTIESFILEMANAGER_HPP__

#include <mtypes/include/types.hpp>
#include "configuration.hpp"
#include "appservice.hpp"
#include "factory.hpp"

namespace lib
{
	class IUserProperties;
	namespace core
	{
		class PropertiesFileManager : public AppService, public FactoryOfSingletons<IUserProperties>
		{
		public:
			PropertiesFileManager();
			virtual ~PropertiesFileManager();

			template <typename T>
			sptr<T> initializeFromFile(const str &fileName) {
				if (typeRegistered<T>()) {
					return getSingleton<T>();
				}
				auto result(registerAndCreateSingleton<T>());
				initialize(fileName, result.get());
				return result;
			}

			template <typename T>
			sptr<T> initializeInMemory() {
				return initializeFromFile<T>("");
			}

		private:
			void initialize(const str &file, IUserProperties *source);
			void initialize(IUserProperties *source);
		};
	}
}

#endif
