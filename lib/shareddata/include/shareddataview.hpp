#pragma once

#ifndef LIB_SHAREDDATA_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define LIB_SHAREDDATA_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/idatawrapper.hpp>

namespace lib::scene
{
/// Component to provide access to resources.
class SharedDataView : public IDataWrapper
{
public:
    void onAttached() override;
};

} // namespace lib::scene

#endif
