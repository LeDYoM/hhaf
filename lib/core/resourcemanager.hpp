#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <lib/include/types.hpp>
#include "configuration.hpp"
#include "appservice.hpp"
#include <list>

namespace lib
{
	namespace draw
	{
		class Font;
		class TextureV1;
	}
	namespace core
	{
		class Resource;

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
			sptr<draw::TextureV1> getTexture(const std::string rid) const;
		private:
			std::list<sptr<draw::Font>> m_fonts;
			std::list<sptr<draw::TextureV1>> m_textures;
		};
	}
}

#endif
