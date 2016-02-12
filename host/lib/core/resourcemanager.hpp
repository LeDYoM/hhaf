#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <lib/include/types.hpp>
#include "exceptions.hpp"
#include "configuration.hpp"
#include "appservice.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace core
	{
		class Resource;

		class ResourceNotFoundException : public excp::BaseException
		{
		public:
			ResourceNotFoundException(const std::string &resourcefn) : BaseException(excp::Severity::FinishApp, "Could not find " + resourcefn) {}
		};

		class ResourceManager : public AppService, public Configuration
		{
		public:
			ResourceManager(core::AppController *appController, const std::string &resourceFile);
			virtual ~ResourceManager();
			sptr<Resource> &getResource(const std::string rid);

		private:
			std::vector<sptr<Resource>> resources;

		};
	}
}

#endif
