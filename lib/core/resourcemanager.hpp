#pragma once

#ifndef LIB_RESOURCEMANAGER_INCLUDE_HPP
#define LIB_RESOURCEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/include/resources/iresourcehandler.hpp>
#include <lib/include/resources/iresourceretriever.hpp>
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
		class ResourceManager final : public AppService, public IResourceHandler, public IResourceRetriever
		{
		public:
			ResourceManager();
			~ResourceManager();

			sptr<scene::TTFont> getFont(const str &rid) override;
			sptr<scene::Texture> getTexture(const str &rid) override;
			sptr<scene::Shader> getShader(const str &rid) override;

            sptr<scene::TTFont> loadFont(const str &rid, const str &fileName) override;
            sptr<scene::Texture> loadTexture(const str &rid, const str &fileName) override;
            sptr<scene::Shader> loadShader(const str &rid, const str &fileName) override;

			template <typename T>
			sptr<T> loadResource(const str &rid, const str &fileName) {
                if constexpr (std::is_same_v<T,scene::TTFont>)
                {
                    return loadFont(rid, fileName);
                }
                else if constexpr (std::is_same_v<T, scene::Texture>)
                {
                    return loadTexture(rid, fileName);
                }
                else if constexpr (std::is_same_v<T, scene::Shader>)
                {
                    return loadShader(rid, fileName);
                }
                else
                {
                    static_assert(false, "Invalid resource type");
                }
            }

            template <typename T>
            sptr<T> getResource(const str &rid) {
                if constexpr (std::is_same_v<T, scene::TTFont>)
                {
                    return getFont(rid);
                }
                else if constexpr (std::is_same_v<T, scene::Texture>)
                {
                    return getTexture(rid);
                }
                else if constexpr (std::is_same_v<T, scene::Shader>)
                {
                    return getShader(rid);
                }
                else
                {
                    static_assert(false, "Invalid resource type");
                }
            }

        private:
            struct ResourceManagerPrivate;
            uptr<ResourceManagerPrivate> m_private;
		};
	}
}

#endif
