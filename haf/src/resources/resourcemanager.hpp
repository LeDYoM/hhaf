#ifndef HAF_RESOURCEMANAGER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>

#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/iresource_configurator.hpp>
#include "system/systembase.hpp"
#include "resources_config_data.hpp"

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
                              public res::IResourcesConfigurator
{
public:
    explicit ResourceManager(sys::SystemProvider& system_provider);
    ~ResourceManager() override;

    types::sptr<res::ITTFont> getTTFont(types::str const& rid) const override;
    types::sptr<res::ITexture> getTexture(types::str const& rid) const override;
    types::sptr<res::IShader> getShader(types::str const& rid) const override;
    types::sptr<res::IFont> getBMPFont(types::str const& rid) const override;

    bool loadTTFont(htps::str const& rid, htps::str const& fileName);
    bool loadTexture(htps::str const& rid, htps::str const& fileName);
    bool loadShader(htps::str const& rid, htps::str const& fileName);
    bool loadBMPFont(htps::str const& rid, htps::str const& fileName);
    bool loadBmpFontTextures(htps::sptr<res::BMPFont> bmp_font,
                             htps::str const& rid,
                             htps::str const& fileName);

    res::SetResourceConfigFileResult setResourceConfigFile(
        types::str const& config_file_name) override;
    bool loadSection(types::str const& section_name) override;
    void setResourcesDirectory(types::str const& directory) override;

    res::SetResourceConfigFileResult parseResourceConfigFile();

private:
    struct ResourceManagerPrivate;
    htps::uptr<ResourceManagerPrivate> p_;
    htps::str resources_config_file_name_;
    res::ResourcesConfigData resources_config_data_;
};

}  // namespace haf::sys

#endif
