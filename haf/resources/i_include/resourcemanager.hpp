#pragma once

#ifndef HAF_RESOURCEMANAGER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <haf/resources/include/iresourcehandler.hpp>
#include <haf/resources/include/iresourceretriever.hpp>
#include <haf/resources/include/iresourceconfigurator.hpp>
#include <system/i_include/appservice.hpp>

namespace haf::scene
{
class BMPFont;
class IFont;
class ITTFont;
class ITexture;
class IShader;
}  // namespace haf::scene

namespace haf::sys
{
class ResourceManager final : public AppService,
                              public IResourceHandler,
                              public IResourceRetriever,
                              public res::IResourcesConfigurator
{
public:
    ResourceManager(sys::SystemProvider& system_provider);
    ~ResourceManager() override;

    mtps::sptr<scene::ITTFont> getTTFont(const mtps::str& rid) override;
    mtps::sptr<scene::ITexture> getTexture(const mtps::str& rid) override;
    mtps::sptr<scene::IShader> getShader(const mtps::str& rid) override;
    mtps::sptr<scene::IFont> getBMPFont(const mtps::str& rid) override;

    bool loadTTFont(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadTexture(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadShader(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadBMPFont(const mtps::str& rid, const mtps::str& fileName) override;

    bool setResourceConfigFile(mtps::str) override;
    bool loadSection(mtps::str const&) override;

private:
    struct ResourceManagerPrivate;
    mtps::uptr<ResourceManagerPrivate> m_private;
};

}  // namespace haf::sys

#endif
