#pragma once

#ifndef LIB_RESOURCEMANAGER_INCLUDE_HPP__
#define LIB_RESOURCEMANAGER_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include "appservice.hpp"

namespace lib
{
	namespace scene
	{
		class TTFont;
		class Texture;
        class Shader;
	}

	namespace core
	{
		class ResourceManager final : public AppService
		{
		public:
			ResourceManager();
			~ResourceManager();

			sptr<scene::TTFont> getFont(const str &rid, const str &fileName);
			sptr<scene::Texture> getTexture(const str &rid, const str &fileName);
			sptr<scene::Shader> getShader(const str &rid, const str &fileName);

			template <typename T>
			sptr<T> getResource(const str &rid, const str &fileName="") {
                if constexpr (std::is_same_v<T,scene::TTFont>) {
                    return getFont(rid, fileName);
                } else {
                    return getTexture(rid, fileName);
                }
            }
		private:
            struct ResourceManagerPrivate;
            uptr<ResourceManagerPrivate> m_private;
		};
	}
}

#endif
