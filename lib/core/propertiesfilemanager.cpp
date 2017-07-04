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

		void PropertiesFileManager::initialize(IUserProperties * source)
		{
			Configuration config("config.cfg");
			source->setProperties(config);
		}


	}
}
