#pragma once

#ifndef LIB_RESOURCE_HANDLER_DATA_WRAPPER_INCLUDE_HPP
#define LIB_RESOURCE_HANDLER_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/idatawrapper.hpp>
#include <lib/resources/include/iresourcehandler.hpp>

namespace lib
{
    class IResourceLoader;
}

namespace lib::scene
{
/// Component to provide access to resources.
class ResourceHandler final : public IDataWrapper, public IResourceHandler
{
public:
    void onAttached() override;
    bool loadTTFont(const str &rid, const str &fileName) override;
    bool loadTexture(const str &rid, const str &fileName) override;
    bool loadShader(const str &rid, const str &fileName) override;
    bool loadBMPFont(const str &rid, const str &fileName) override;
    void loadResources(IResourceLoader& resource_loader);

private:
    rptr<IResourceHandler> handler_;
};
} // namespace lib::scene

#endif
