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
		class TTFont;
		class Texture;
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
				if (typeid(T) == typeid(draw::TTFont)) {
					return getFont(rid);
				}
				else {
					return getTexture(rid);
				}
			}
			sptr<draw::TTFont> getFont(const str &rid) const;
			sptr<draw::Texture> getTexture(const str &rid) const;

			template <typename T>
			using NamedIndex = std::pair<const str, T>;

			template <typename T>
			using ResourceList = std::list<NamedIndex<T>>;

		private:
			ResourceList<sptr<draw::TTFont>> m_fonts;
			ResourceList<sptr<draw::Texture>> m_textures;
		};
	}
}

#endif
