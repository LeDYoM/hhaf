#pragma once

#ifndef LIB_RESOURCEMANAGER_INCLUDE_HPP
#define LIB_RESOURCEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/resources/include/iresourcehandler.hpp>
#include <lib/resources/include/iresourceretriever.hpp>
#include <lib/system/appservice.hpp>

namespace lib::scene
{
    class BMPFont;
    class TTFont;
    class Texture;
    class Shader;
}

namespace lib::sys
{
    class ResourceManager final : public HostedAppService, public IResourceHandler, public IResourceRetriever
    {
    public:
        ResourceManager(sys::SystemProvider &system_provider);
        ~ResourceManager() override;

        sptr<scene::ITTFont> getTTFont(const str &rid) override;
        sptr<scene::ITexture> getTexture(const str &rid) override;
        sptr<scene::IShader> getShader(const str &rid) override;
        sptr<scene::IFont> getBMPFont(const str &rid) override;

        sptr<scene::TTFont> loadTTFont(const str &rid, const str &fileName) override;
        sptr<scene::Texture> loadTexture(const str &rid, const str &fileName) override;
        sptr<scene::Shader> loadShader(const str &rid, const str &fileName) override;
        sptr<scene::BMPFont> loadBMPFont(const str &rid, const str &fileName) override;

    private:
        struct ResourceManagerPrivate;
        uptr<ResourceManagerPrivate> m_private;
    };
}

#endif
