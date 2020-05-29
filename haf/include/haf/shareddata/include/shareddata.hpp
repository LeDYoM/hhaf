#pragma once

#ifndef HAF_SHAREDDATA_DATA_WRAPPER_INCLUDE_HPP
#define HAF_SHAREDDATA_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/shareddata/include/ishareable.hpp>

namespace haf::shdata
{
/**
 * @brief Component to provide access to data resources.
 *
 */
class SharedData : public sys::IDataWrapper
{
public:
    bool store(mtps::uptr<IShareable> data);

    template <typename T>
    void store(mtps::uptr<T> data)
    {
        store(unique_pointer_cast<IShareable>(std::move(data)));
    }

    template <typename T = IShareable>
    [[nodiscard]] mtps::uptr<T> retrieve()
    {
        return unique_pointer_cast<T>(retrieve_imp());
    }

    [[nodiscard]] bool isEmpty();
    bool makeEmpty();

private:
    [[nodiscard]] mtps::uptr<IShareable> retrieve_imp();
};

}  // namespace haf::shdata

#endif
