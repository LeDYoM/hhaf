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
    class IFont;
    class ITTFont;
    class ITexture;
    class IShader;
}

namespace lib::sys
{
    class ResourceManager final : public AppService, 
    public IResourceHandler, public IResourceRetriever
    {
    public:
        ResourceManager(sys::SystemProvider &system_provider);
        ~ResourceManager() override;

        sptr<scene::ITTFont> getTTFont(const str &rid) override;
        sptr<scene::ITexture> getTexture(const str &rid) override;
        sptr<scene::IShader> getShader(const str &rid) override;
        sptr<scene::IFont> getBMPFont(const str &rid) override;

        bool loadTTFont(const str &rid, const str &fileName) override;
        bool loadTexture(const str &rid, const str &fileName) override;
        bool loadShader(const str &rid, const str &fileName) override;
        bool loadBMPFont(const str &rid, const str &fileName) override;

    private:
        struct ResourceManagerPrivate;
        uptr<ResourceManagerPrivate> m_private;
    };
}

#endif
