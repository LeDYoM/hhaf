#pragma once

#ifndef LIB_IAPP_INCLUDE_HPP
#define LIB_IAPP_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::sys
{
class ISystemProvider;
} // namespace lib::sys

namespace lib
{
class IApp
{
public:
    constexpr IApp() noexcept {}
    virtual ~IApp() noexcept {}

    virtual void onInit(sys::ISystemProvider& system_provider) = 0;
    virtual void onFinish(sys::ISystemProvider& system_provider) = 0;

    virtual u16 getVersion() const noexcept = 0;
    virtual u16 getSubVersion() const noexcept = 0;
    virtual u16 getPatch() const noexcept = 0;
    virtual str getName() const noexcept = 0;
};
} // namespace lib

using p_initApp = lib::IApp *(*)();
using p_finishApp = bool (*)(lib::IApp *const);

#endif
