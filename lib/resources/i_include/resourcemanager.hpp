#pragma once

#ifndef LIB_RESOURCEMANAGER_INCLUDE_HPP
#define LIB_RESOURCEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/resources/include/iresourcehandler.hpp>
#include <lib/resources/include/iresourceretriever.hpp>
#include <lib/system/include/appservice.hpp>

namespace haf::scene
{
    class BMPFont;
    class IFont;
    class ITTFont;
    class ITexture;
    class IShader;
}

namespace haf::sys
{
    class ResourceManager final : public AppService, 
    public IResourceHandler, public IResourceRetriever
    {
    public:
        ResourceManager(sys::SystemProvider &system_provider);
        ~ResourceManager() override;

        mtps::sptr<scene::ITTFont> getTTFont(const mtps::str &rid) override;
        mtps::sptr<scene::ITexture> getTexture(const mtps::str &rid) override;
        mtps::sptr<scene::IShader> getShader(const mtps::str &rid) override;
        mtps::sptr<scene::IFont> getBMPFont(const mtps::str &rid) override;

        bool loadTTFont(const mtps::str &rid, const mtps::str &fileName) override;
        bool loadTexture(const mtps::str &rid, const mtps::str &fileName) override;
        bool loadShader(const mtps::str &rid, const mtps::str &fileName) override;
        bool loadBMPFont(const mtps::str &rid, const mtps::str &fileName) override;

    private:
        struct ResourceManagerPrivate;
        mtps::uptr<ResourceManagerPrivate> m_private;
    };
}

#endif
