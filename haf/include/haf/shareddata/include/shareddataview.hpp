#pragma once

#ifndef HAF_SHAREDDATA_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_SHAREDDATA_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/shareddata/include/ishareable.hpp>

namespace haf::shdata
{
/**
 * @brief Component to provide access to data resources.
 * 
 */
class SharedDataView : public sys::IDataWrapper
{
public:
    ~SharedDataView() override;

    void onAttached() override;

    [[nodiscard]] IShareable& data();
    [[nodiscard]] const IShareable& data() const;

    template <typename T>
    [[nodiscard]] T& dataAs()
    {
        return dynamic_cast<T&>(data());
    }

    template <typename T>
    [[nodiscard]] const T& dataAs() const
    {
        return dynamic_cast<T&>(data());
    }

private:
    mtps::uptr<IShareable> data_;
};

} // namespace haf::scene

#endif
