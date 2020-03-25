#pragma once

#ifndef LIB_SHAREDDATA_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define LIB_SHAREDDATA_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/include/idatawrapper.hpp>
#include <lib/shareddata/include/ishareable.hpp>

namespace lib::shdata
{
/// Component to provide access to data resources.
class SharedData : public sys::IDataWrapper
{
public:
    void store(mtps::uptr<IShareable> data);

    template <typename T>
    void store(mtps::uptr<T> data)
    {
        store(unique_pointer_cast<IShareable>(std::move(data)));
    }

    template <typename T = IShareable>
    [[nodiscard]] mtps::uptr<T> retrieve()
    {
        return unique_pointer_cast<T>(std::move(retrieve_imp()));
    }

    [[nodiscard]] bool isEmpty();
private:
    [[nodiscard]] mtps::uptr<IShareable> retrieve_imp();
};

class SharedDataView : public sys::IDataWrapper
{
public:
    SharedDataView();
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

} // namespace lib::scene

#endif
