#ifndef HAF_HAF_APP_MIDDLEWARE_INCLUDE_HPP
#define HAF_HAF_APP_MIDDLEWARE_INCLUDE_HPP

#include <hosted_app/include/iapp.hpp>
#include <htypes/include/types.hpp>
#include <haf_user/include/iapp_with_default_app_versioning_system.hpp>
#include <haf_user/include/iapp_with_host_access.hpp>
#include "app_version.hpp"

namespace haf::app_middleware
{
class HafAppMiddleware final
    : public user::IAppWithHostAccess<user::IAppWithDefaultVersionSystem<cl_version::AppVersion>>
{
public:
    HafAppMiddleware();
    ~HafAppMiddleware() override;

    void onInit(scene::AppInitializer& app_initializer) override;
    void onFinish(scene::AppFinisher& app_finisher) override;
    void onHostInit(host::HostCommunication&) override;
};
}  // namespace haf::app_middleware

#endif