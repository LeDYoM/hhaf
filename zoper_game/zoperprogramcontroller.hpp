#pragma once

#ifndef LIB_ZOPERPROGRAMCONTROLLER_HPP
#define LIB_ZOPERPROGRAMCONTROLLER_HPP

#include <hosted_app/include/iapp.hpp>
#include <mtypes/include/types.hpp>

namespace lib::sys
{
    class ISystemProvider;
}

namespace zoper
{
class KeyMapping;

class ZoperProgramController : public lib::IApp
{
public:
    ZoperProgramController();
    ~ZoperProgramController() override;

    void onInit(lib::sys::ISystemProvider& system_provider) override;
    void onFinish(lib::sys::ISystemProvider& system_provider) override;

    lib::u16 getVersion() const noexcept override;
    lib::u16 getSubVersion() const noexcept override;
    lib::u16 getPatch() const noexcept override;
    lib::str getName() const noexcept override;

    lib::uptr<KeyMapping> keyMapping;
};
} // namespace zoper

#endif