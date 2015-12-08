#include "resourcemanager.hpp"
#include "../log.hpp"

namespace lib
{
	namespace scn
	{
		ResourceManager::ResourceManager()
			: Configuration{ "res.cfg" }
		{
			if (!configFileExists("res.cfg"))
			{
				LOG_ERROR("Error: Resource definition file res.cfg does not exists");
			}
			else
			{

			}
		}


		ResourceManager::~ResourceManager()
		{
		}
	}
}
