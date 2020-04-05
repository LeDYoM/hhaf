#pragma once

#ifndef LIB_IAPP_INCLUDE_HPP
#define LIB_IAPP_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace haf::sys
{
class ISystemProvider;
} // namespace haf::sys

namespace haf
{
class IApp
{
public:
    constexpr IApp() noexcept {}
    virtual ~IApp() noexcept {}

    virtual void onInit(sys::ISystemProvider& system_provider) = 0;
    virtual void onFinish(sys::ISystemProvider& system_provider) = 0;

    virtual mtps::u16 getVersion() const noexcept = 0;
    virtual mtps::u16 getSubVersion() const noexcept = 0;
    virtual mtps::u16 getPatch() const noexcept = 0;
    virtual mtps::str getName() const noexcept = 0;
};
} // namespace haf

using p_initApp = haf::IApp *(*)();
using p_finishApp = bool (*)(haf::IApp *const);

#endif
