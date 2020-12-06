#ifndef HAF_HAF_APP_MENU_INCLUDE_HPP
#define HAF_HAF_APP_MENU_INCLUDE_HPP

#include <hosted_app/include/iapp.hpp>
#include <mtypes/include/types.hpp>
#include <haf_user/include/iapp_with_default_app_versioning_system.hpp>
#include "app_version.hpp"

namespace haf::app_menu
{
class HafAppMenu final
    : public haf::user::IAppWithDefaultVersionSystem<cl_version::AppVersion>
{
public:
    HafAppMenu();
    ~HafAppMenu() override;

    void onInit(haf::sys::DataWrapperCreator& data_wrapper_creator) override;
    void onFinish(haf::sys::DataWrapperCreator& data_wrapper_creator) override;

    void configureScenes(haf::sys::DataWrapperCreator& data_wrapper_creator);
};
}  // namespace zoper

#endif