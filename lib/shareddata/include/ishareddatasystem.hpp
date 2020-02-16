#pragma once

#ifndef LIB_SYSTEM_ISHARED_DATA_INTERFACE_INCLUDE_HPP
#define LIB_SYSTEM_ISHARED_DATA_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/shareddata/include/ishareable.hpp>

namespace lib::sys
{

class ISharedDataSystem
{
public:
    virtual void store(uptr<shdata::IShareable> data) noexcept = 0;
    [[nodiscard]] virtual uptr<shdata::IShareable> retrieve() noexcept = 0;

    virtual bool isEmpty() const noexcept = 0;
    virtual bool makeEmpty() = 0;
};
} // namespace lib::sys

#endif
