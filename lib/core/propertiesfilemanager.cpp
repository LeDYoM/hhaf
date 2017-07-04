#include "propertiesfilemanager.hpp"
#include <mtypes/include/log.hpp>
#include "configuration.hpp"
#include "iuserproperties.hpp"

namespace lib
{
	namespace core
	{
		PropertiesFileManager::PropertiesFileManager() = default;
		PropertiesFileManager::~PropertiesFileManager() = default;

		void PropertiesFileManager::initialize(const str &file, IUserProperties *source)
		{
			Configuration config(file);
			source->setProperties(config);
		}
	}
}
