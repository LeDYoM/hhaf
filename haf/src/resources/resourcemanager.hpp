#ifndef HAF_RESOURCEMANAGER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/resources/resourceretriever.hpp>
#include <haf/include/resources/resourceconfigurator.hpp>
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
class ResourceManager final : public SystemBase
{
public:
    ResourceManager(sys::SystemProvider& system_provider);
    ~ResourceManager();

    htps::sptr<res::ITTFont> getTTFont(const htps::str& rid) const;
    htps::sptr<res::ITexture> getTexture(const htps::str& rid) const;
    htps::sptr<res::IShader> getShader(const htps::str& rid) const;
    htps::sptr<res::IFont> getBMPFont(const htps::str& rid) const;

    bool loadTTFont(const htps::str& rid, const htps::str& fileName);
    bool loadTexture(const htps::str& rid, const htps::str& fileName);
    bool loadShader(const htps::str& rid, const htps::str& fileName);
    bool loadBMPFont(const htps::str& rid, const htps::str& fileName);
    bool loadBmpFontTextures(htps::sptr<res::BMPFont> bmp_font,
                             const htps::str& rid,
                             const htps::str& fileName);

    res::SetResourceConfigFileResult setResourceConfigFile(
        htps::str config_file_name);
    bool loadSection(htps::str const& section_name);
    void setResourcesDirectory(htps::str directory);

    res::SetResourceConfigFileResult parseResourceConfigFile();

private:
    struct ResourceManagerPrivate;
    htps::uptr<ResourceManagerPrivate> p_;
    htps::str resources_config_file_name_;
    res::ResourcesConfigData resources_config_data_;
};

}  // namespace haf::sys

#endif
