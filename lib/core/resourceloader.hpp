#pragma once

#ifndef LIB_RESOURCELOADER_INCLUDE_HPP__
#define LIB_RESOURCELOADER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include "iuserproperties.hpp"
#include "resourcetypes.hpp"

namespace lib
{
	namespace scene
	{
		class TTFont;
		class Texture;
	}
	namespace core
	{
		class ResourceManager;
		/**
		* This class acts as a controller for loading resources. The @IResourceList will receive it as parameter.
		* Call the public methods to add your petitions of loading resources to the queue.
		*/
		class ResourceLoader final
		{
		public:
			ResourceLoader();
			~ResourceLoader();

			void addToLoadList(const str&fileName);

			sptr<scene::Texture> getLoadedResourceTexture(const str&fileName);
			sptr<scene::Texture> getLoadedResourceTTFont(const str&fileName);

		private:

			bool ensureLoad(ResourceManager &);

			vector<str> m_fileNames;
			friend class ResourceManager;
		};
	}
}

#endif
