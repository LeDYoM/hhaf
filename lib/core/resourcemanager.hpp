#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <mtypes/include/types.hpp>
#include "configuration.hpp"
#include "appservice.hpp"
#include "resourcetypes.hpp"

namespace lib
{
	class IResourcesList;

	namespace scene
	{
		class TTFont;
		class Texture;
	}
	namespace core
	{
		class ResourceLoader;

		class ResourceManager : public AppService, public Configuration
		{
		public:
			ResourceManager(const str &resourceFile);
			~ResourceManager();

			template <typename T>
			sptr<T> getResource(const str& rid) const;

			template <>
			sptr<scene::TTFont> getResource<scene::TTFont>(const str& rid) const {
				return getFont(rid);
			}

			template <>
			sptr<scene::Texture> getResource<scene::Texture>(const str& rid) const {
				return getTexture(rid);
			}

			sptr<scene::TTFont> getFont(const str &rid) const;
			sptr<scene::Texture> getTexture(const str &rid) const;

			///// New API
			u32 loadFontList(ResourceList<sptr<scene::TTFont>> &fileList);
			u32 loadTextureList(ResourceList<sptr<scene::Texture>> &fileList);

			void registerResourceList(sptr<IResourcesList>);

			template <typename T>
			bool ensureLoaded(sptr<T>&iilist) {
				return ensureLoadedInternal(std::dynamic_pointer_cast<IResourcesList>(iilist));
			}

		private:
			template <typename T>
			sptr<T> getOrLoadResource(const str&);

			template <>
			sptr<scene::TTFont> getOrLoadResource(const str&address) {
				return getOrLoadTTFont(address);
			}

			template <>
			sptr<scene::Texture> getOrLoadResource(const str&address) {
				return getOrLoadTexture(address);
			}

			sptr<scene::TTFont> getOrLoadTTFont(const str&address);
			sptr<scene::Texture> getOrLoadTexture(const str&address);

			bool ensureLoadedInternal(sptr<IResourcesList>&);
			ResourceList<sptr<scene::TTFont>> m_fonts;
			ResourceList<sptr<scene::Texture>> m_textures;
			std::list<std::pair<sptr<ResourceLoader>,sptr<IResourcesList>>> m_resourceListList;
		};
	}
}

#endif
