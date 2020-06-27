#pragma once

#ifndef HAF_RESOURCE_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_RESOURCE_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/resources/include/iresourceretriever.hpp>

namespace haf::res
{
/// Component to provide access to resources.
class ResourceView final : public sys::IDataWrapper, public IResourceRetriever
{
public:
    void onAttached() override;
    mtps::sptr<ITTFont> getTTFont(const mtps::str& rid) const override;
    mtps::sptr<ITexture> getTexture(const mtps::str& rid) const override;
    mtps::sptr<IShader> getShader(const mtps::str& rid) const override;
    mtps::sptr<IFont> getBMPFont(const mtps::str& rid) const override;

private:
    mtps::rptr<IResourceRetriever> retriever_;
};
}  // namespace haf::res

#endif
