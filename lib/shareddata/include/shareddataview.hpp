#pragma once

#ifndef LIB_SHAREDDATA_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define LIB_SHAREDDATA_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/idatawrapper.hpp>
#include <lib/shareddata/include/ishareable.hpp>

namespace lib::shdata
{
/// Component to provide access to resources.
class SharedDataView : public scene::IDataWrapper
{
public:
    void onAttached() override;

    void store(uptr<IShareable> data);
    uptr<IShareable> retrieve();

    template <typename T>
    uptr<T> retrive()
    {
        return retrieve();
    }

};

} // namespace lib::scene

#endif
