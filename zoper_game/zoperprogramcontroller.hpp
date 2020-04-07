#pragma once

#ifndef HAF_ZOPERPROGRAMCONTROLLER_HPP
#define HAF_ZOPERPROGRAMCONTROLLER_HPP

#include <hosted_app/include/iapp.hpp>
#include <mtypes/include/types.hpp>

namespace haf::sys
{
    class ISystemProvider;
}

namespace zoper
{
class KeyMapping;

class ZoperProgramController : public haf::IApp
{
public:
    ZoperProgramController();
    ~ZoperProgramController() override;

    void onInit(haf::sys::ISystemProvider& system_provider) override;
    void onFinish(haf::sys::ISystemProvider& system_provider) override;

    mtps::u16 getVersion() const noexcept override;
    mtps::u16 getSubVersion() const noexcept override;
    mtps::u16 getPatch() const noexcept override;
    mtps::str getName() const noexcept override;

    mtps::uptr<KeyMapping> keyMapping;
};
} // namespace zoper

#endif