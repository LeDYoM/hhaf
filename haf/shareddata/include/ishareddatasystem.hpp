#pragma once

#ifndef HAF_SYSTEM_ISHARED_DATA_INTERFACE_INCLUDE_HPP
#define HAF_SYSTEM_ISHARED_DATA_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/shareddata/include/ishareable.hpp>

namespace haf::sys
{

class ISharedDataSystem
{
public:
    virtual void store(mtps::uptr<shdata::IShareable> data) noexcept = 0;
    [[nodiscard]] virtual mtps::uptr<shdata::IShareable> retrieve() noexcept = 0;

    virtual bool isEmpty() const noexcept = 0;
    virtual bool makeEmpty() = 0;
};
} // namespace haf::sys

#endif
