#pragma once

#ifndef LIB_RESOURCE_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define LIB_RESOURCE_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "idatawrapper.hpp"
#include <lib/include/resources/iresourceretriever.hpp>

namespace lib::scene
{
    /// Component to provide access to resources.
    class ResourceView final : public IDataWrapper, public IResourceRetriever
	{
	public:
        ~ResourceView() override;

        sptr<scene::ITTFont> getFont(const str &rid) override;
        sptr<scene::ITexture> getTexture(const str &rid) override;
        sptr<scene::IShader> getShader(const str &rid) override;
	};
}

#endif
