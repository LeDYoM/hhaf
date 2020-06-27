#pragma once

#ifndef HAF_RESOURCEMANAGER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <haf/resources/include/iresourcehandler.hpp>
#include <haf/resources/include/iresourceretriever.hpp>
#include <haf/resources/include/iresourceconfigurator.hpp>
#include <system/i_include/systembase.hpp>
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
                              public res::IResourceHandler,
                              public res::IResourceRetriever,
                              public res::IResourcesConfigurator
{
public:
    ResourceManager(sys::SystemProvider& system_provider);
    ~ResourceManager() noexcept override;

    mtps::sptr<res::ITTFont> getTTFont(const mtps::str& rid) override;
    mtps::sptr<res::ITexture> getTexture(const mtps::str& rid) override;
    mtps::sptr<res::IShader> getShader(const mtps::str& rid) override;
    mtps::sptr<res::IFont> getBMPFont(const mtps::str& rid) override;

    bool loadTTFont(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadTexture(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadShader(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadBMPFont(const mtps::str& rid, const mtps::str& fileName) override;

    bool setResourceConfigFile(mtps::str config_file_name) override;
    bool loadSection(mtps::str const& section_name) override;
    bool parseResourceConfigFile();

private:
    struct ResourceManagerPrivate;
    mtps::uptr<ResourceManagerPrivate> p_;
    mtps::str resources_config_file_name_;
    res::ResourcesConfigData resources_config_data_;
};

}  // namespace haf::sys

#endif
