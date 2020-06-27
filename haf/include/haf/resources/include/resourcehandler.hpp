#pragma once

#ifndef HAF_RESOURCE_HANDLER_DATA_WRAPPER_INCLUDE_HPP
#define HAF_RESOURCE_HANDLER_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/resources/include/iresourcehandler.hpp>

namespace haf::res
{
/// Component to provide access to resources.
class ResourceHandler final : public sys::IDataWrapper,
                              public IResourceHandler
{
public:
    void onAttached() override;
    bool loadTTFont(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadTexture(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadShader(const mtps::str& rid, const mtps::str& fileName) override;
    bool loadBMPFont(const mtps::str& rid, const mtps::str& fileName) override;

private:
    mtps::rptr<IResourceHandler> handler_;
};
}  // namespace haf::res

#endif
