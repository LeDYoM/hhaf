#ifndef HAF_HAF_APP_MENU_INCLUDE_HPP
#define HAF_HAF_APP_MENU_INCLUDE_HPP

#include <hosted_app/include/iapp.hpp>
#include <htypes/include/types.hpp>
#include <haf_user/include/iapp_with_default_app_versioning_system.hpp>

namespace haf::app_menu
{
class HafAppMenu final
    : public haf::user::IAppWithDefaultVersionSystem<1,2,3,4>
{
public:
    HafAppMenu();
    ~HafAppMenu() override;

    void onInit(scene::AppInitializer& app_initializer) override;
    void onFinish(scene::AppFinisher& app_finisher) override;

    htps::str getName() const noexcept override { return "Menu App"; }
};
}  // namespace haf::app_menu

#endif