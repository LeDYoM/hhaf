#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <lib/include/types.hpp>
#include "configuration.hpp"
#include "appservice.hpp"
#include <list>

namespace lib
{
	namespace scene
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
			ResourceManager(const str &resourceFile);
			~ResourceManager();

			template <typename T>
			sptr<T> getResource(const str rid) const
			{
				if (typeid(T) == typeid(scene::TTFont)) {
					return getFont(rid);
				}
				else {
					return getTexture(rid);
				}
			}
			sptr<scene::TTFont> getFont(const str &rid) const;
			sptr<scene::Texture> getTexture(const str &rid) const;

			template <typename T>
			using NamedIndex = std::pair<const str, T>;

			template <typename T>
			using ResourceList = std::list<NamedIndex<T>>;

		private:
			ResourceList<sptr<scene::TTFont>> m_fonts;
			ResourceList<sptr<scene::Texture>> m_textures;
		};
	}
}

#endif
