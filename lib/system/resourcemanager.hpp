#pragma once

#ifndef LIB_RESOURCEMANAGER_INCLUDE_HPP
#define LIB_RESOURCEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/include/resources/iresourcehandler.hpp>
#include <lib/include/resources/iresourceretriever.hpp>
#include <lib/system/appservice.hpp>

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
        class Host;
		class ResourceManager final : public HostedAppService, public IResourceHandler, public IResourceRetriever
		{
		public:
			ResourceManager(core::SystemProvider &system_provider);
			~ResourceManager() override;

			sptr<scene::ITTFont> getFont(const str &rid) override;
			sptr<scene::ITexture> getTexture(const str &rid) override;
			sptr<scene::IShader> getShader(const str &rid) override;

            sptr<scene::TTFont> loadFont(const str &rid, const str &fileName) override;
            sptr<scene::Texture> loadTexture(const str &rid, const str &fileName) override;
            sptr<scene::Shader> loadShader(const str &rid, const str &fileName) override;

			template <typename T>
			sptr<T> loadResource(const str &rid, const str &fileName) {
                if constexpr (std::is_same_v<T,scene::ITTFont>)
                {
                    return loadFont(rid, fileName);
                }
                else if constexpr (std::is_same_v<T, scene::ITexture>)
                {
                    return loadTexture(rid, fileName);
                }
                else if constexpr (std::is_same_v<T, scene::IShader>)
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
                if constexpr (std::is_same_v<T, scene::ITTFont>)
                {
                    return getFont(rid);
                }
                else if constexpr (std::is_same_v<T, scene::ITexture>)
                {
                    return getTexture(rid);
                }
                else if constexpr (std::is_same_v<T, scene::IShader>)
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
