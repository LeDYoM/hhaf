#pragma once

#ifndef LIB_RESOURCEMANAGER_INCLUDE_HPP
#define LIB_RESOURCEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/include/resources/iresourcehandler.hpp>
#include <lib/include/resources/iresourceretriever.hpp>
#include <lib/system/appservice.hpp>

namespace lib::scene
{
    class BMPFont;
    class TTFont;
    class Texture;
    class Shader;
}

namespace lib::core
{
    class ResourceManager final : public HostedAppService, public IResourceHandler, public IResourceRetriever
    {
    public:
        ResourceManager(core::SystemProvider &system_provider);
        ~ResourceManager() override;

        sptr<scene::ITTFont> getFont(const str &rid) override;
        sptr<scene::ITexture> getTexture(const str &rid) override;
        sptr<scene::IShader> getShader(const str &rid) override;
        sptr<scene::IFont> getBMPFont(const str &rid) override;

        sptr<scene::TTFont> loadFont(const str &rid, const str &fileName) override;
        sptr<scene::Texture> loadTexture(const str &rid, const str &fileName) override;
        sptr<scene::Shader> loadShader(const str &rid, const str &fileName) override;
        sptr<scene::BMPFont> loadBMPFont(const str &rid, const str &fileName) override;

    private:
        struct ResourceManagerPrivate;
        uptr<ResourceManagerPrivate> m_private;
    };
}

#endif
