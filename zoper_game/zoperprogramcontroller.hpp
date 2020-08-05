#pragma once

#ifndef HAF_ZOPERPROGRAMCONTROLLER_HPP
#define HAF_ZOPERPROGRAMCONTROLLER_HPP

#include <hosted_app/include/iapp.hpp>
#include <mtypes/include/types.hpp>
#include <haf_user/include/iapp_with_default_app_versioning_system.hpp>
#include "app_version.hpp"

namespace zoper
{
class KeyMapping;

class ZoperProgramController final
    : public haf::user::IAppWithDefaultVersionSystem<cl_version::AppVersion>
{
public:
    ZoperProgramController();
    ~ZoperProgramController() override;

    void onInit(haf::sys::DataWrapperCreator& data_wrapper_creator) override;
    void onFinish(haf::sys::DataWrapperCreator& data_wrapper_creator) override;

    void configureScenes(haf::sys::DataWrapperCreator& data_wrapper_creator);
    mtps::uptr<KeyMapping> keyMapping;
};
}  // namespace zoper

#endif