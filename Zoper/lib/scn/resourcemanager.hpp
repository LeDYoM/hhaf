#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include "../types.hpp"
#include "../configuration.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace scn
	{
		class Resource;

		class ResourceManager : public Configuration
		{
		public:
			ResourceManager(const std::string &resourceFile);
			virtual ~ResourceManager();
			uptr<Resource> &getResource(const std::string rid);

		private:
			std::vector<uptr<Resource>> resources;

		};
	}
}

#endif
