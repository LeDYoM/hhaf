HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCEMANAGER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/resources/idefault_resources_retriever.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/iresource_configurator.hpp>
#include <haf/include/resources/resource_descriptor.hpp>
#include <backend_dev/include/iresource_manager.hpp>
#include <backend_dev/include/iresource_descriptor.hpp>

#include "system/system_base.hpp"
#include "resources_config_data.hpp"
#include "resource_manager_config_loader.hpp"
#include "resource_loaders/iresource_loader.hpp"

namespace haf::res
{
class BMPFont;
class IFont;
class ITTFont;
class ITexture;
class IShader;
}  // namespace haf::res

namespace haf::sys
{
class ResourceManager final : public SystemBase,
                              public res::IResourceRetriever,
                              public res::IResourcesConfigurator,
                              public res::IDefaultResourcesRetriever,
                              public res::IResourceLoader,
                              public backend::IResourceManager
{
public:
    explicit ResourceManager(sys::SystemProvider& system_provider);
    ~ResourceManager();

    void init();
    htps::sptr<res::ITTFont> getTTFont(htps::str const& rid) const override;
    htps::sptr<res::ITexture> getTexture(htps::str const& rid) const override;
    htps::sptr<res::IShader> getShader(htps::str const& rid) const override;
    htps::sptr<res::IFont> getBMPFont(htps::str const& rid) const override;

    bool loadResourceForResource(
        backend::IResourceDescriptor const& resource_descriptor) override;
    bool setExternalTexture(htps::str const& rid,
                            backend::ITexture const* texture) override;

    bool loadResource(
        res::ResourceDescriptor const& resource_descriptor) override;
    bool loadTTFont(htps::str const& rid, htps::str const& fileName);
    bool loadTexture(htps::str const& rid, htps::str const& fileName);
    bool loadShader(htps::str const& rid, htps::str const& fileName);
    bool loadBMPFont(htps::str const& rid, htps::str const& fileName);
    bool loadBmpFontTextures(htps::sptr<res::BMPFont> bmp_font,
                             htps::str const& rid);

    res::SetResourceConfigFileResult setResourceConfigFile(
        htps::str const& config_file_name) override;
    bool loadSection(htps::str const& section_name) override;
    void setResourcesDirectory(htps::str const& directory) override;

    htps::sptr<res::IShader> getDefaultShader() const override;

private:
    bool loadEmbeddedResources();

    struct ResourceManagerPrivate;
    htps::uptr<ResourceManagerPrivate> p_;
    res::ResourceManagerConfigLoader config_loader_;
    res::ResourcesConfigData resources_config_data_;
};

}  // namespace haf::sys

#endif
