#ifndef HAF_ZOPERPROGRAMCONTROLLER_HPP
#define HAF_ZOPERPROGRAMCONTROLLER_HPP

#include <hosted_app/include/iapp.hpp>
#include <htypes/include/types.hpp>
#include <haf_user/include/iapp_with_default_app_versioning_system.hpp>
#include "app_version.hpp"

namespace zoper
{
class ZoperProgramController final
    : public haf::user::IAppWithDefaultVersionSystem<cl_version::AppVersion>
{
public:
    void onInit(
        haf::scene::AppInitializer& app_initializer) override;
    void onFinish(haf::scene::AppFinisher& app_finisher) override;

private:
    void configureScenes(haf::scene::AppInitializer& app_initializer);
};
}  // namespace zoper

#endif
