#pragma once

#ifndef HAF_RESOURCE_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_RESOURCE_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/resources/include/iresourceretriever.hpp>

namespace haf::scene
{
/// Component to provide access to resources.
class ResourceView final : public sys::IDataWrapper, public IResourceRetriever
{
public:
    void onAttached() override;
    mtps::sptr<scene::ITTFont> getTTFont(const mtps::str& rid) override;
    mtps::sptr<scene::ITexture> getTexture(const mtps::str& rid) override;
    mtps::sptr<scene::IShader> getShader(const mtps::str& rid) override;
    mtps::sptr<scene::IFont> getBMPFont(const mtps::str& rid) override;

private:
    mtps::rptr<IResourceRetriever> retriever_;
};
}  // namespace haf::scene

#endif
