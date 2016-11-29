#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <lib/include/types.hpp>
#include "exceptions.hpp"
#include "configuration.hpp"
#include "appservice.hpp"
#include <list>

namespace lib
{
	namespace draw
	{
		class Font;
		class Texture;
	}
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
			ResourceManager(const std::string &resourceFile);
			~ResourceManager();

			template <typename T>
			sptr<T> getResource(const std::string rid) const
			{
				if (typeid(T) == typeid(draw::Font)) {
					return getFont(rid);
				}
				else {
					return getTexture(rid);
				}
			}
			sptr<draw::Font> getFont(const std::string rid) const;
			sptr<draw::Texture> getTexture(const std::string rid) const;
		private:
			std::list<sptr<draw::Font>> m_fonts;
			std::list<sptr<draw::Texture>> m_textures;
		};
	}
}

#endif
