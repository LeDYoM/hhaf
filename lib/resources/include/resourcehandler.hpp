#pragma once

#ifndef LIB_RESOURCE_HANDLER_DATA_WRAPPER_INCLUDE_HPP
#define LIB_RESOURCE_HANDLER_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/include/idatawrapper.hpp>
#include <lib/resources/include/iresourcehandler.hpp>

namespace lib
{
    class IResourceLoader;
}

namespace lib::scene
{
/// Component to provide access to resources.
class ResourceHandler final : public sys::IDataWrapper, public IResourceHandler
{
public:
    void onAttached() override;
    bool loadTTFont(const mtps::str&rid, const mtps::str&fileName) override;
    bool loadTexture(const mtps::str&rid, const mtps::str&fileName) override;
    bool loadShader(const mtps::str&rid, const mtps::str&fileName) override;
    bool loadBMPFont(const mtps::str&rid, const mtps::str&fileName) override;
    void loadResources(IResourceLoader& resource_loader);

private:
    mtps::rptr<IResourceHandler> handler_;
};
} // namespace lib::scene

#endif
