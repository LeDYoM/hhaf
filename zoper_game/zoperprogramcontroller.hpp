#pragma once

#ifndef HAF_ZOPERPROGRAMCONTROLLER_HPP
#define HAF_ZOPERPROGRAMCONTROLLER_HPP

#include <hosted_app/include/iapp.hpp>
#include <mtypes/include/types.hpp>
#include <haf_user/include/iapp_with_default_app_versioning_system.hpp>

namespace haf::sys
{
    class DataWrapperCreator;
}

namespace zoper
{
class KeyMapping;

class ZoperProgramController : public haf::user::IAppWithDefaultVersionSystem
{
public:
    ZoperProgramController();
    ~ZoperProgramController() override;

    void onInit(haf::sys::DataWrapperCreator &data_wrapper_creator) override;
    void onFinish(haf::sys::DataWrapperCreator &data_wrapper_creator) override;
/*
    mtps::u16 getVersion() const noexcept override;
    mtps::u16 getSubVersion() const noexcept override;
    mtps::u16 getPatch() const noexcept override;
    mtps::str getName() const noexcept override;
*/
    mtps::uptr<KeyMapping> keyMapping;
};
} // namespace zoper

#endif