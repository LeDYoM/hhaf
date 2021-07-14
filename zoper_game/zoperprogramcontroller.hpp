#ifndef HAF_ZOPERPROGRAMCONTROLLER_HPP
#define HAF_ZOPERPROGRAMCONTROLLER_HPP

#include <hosted_app/include/iapp.hpp>
#include <haf_user/include/iapp_with_default_app_versioning_system.hpp>
#include <htypes/include/types.hpp>

namespace zoper
{
constexpr char const Zoper_name[] = Zoper_NAME;

class ZoperProgramController final
    : public haf::user::IAppWithDefaultVersionSystem<Zoper_VERSION,
                                                     Zoper_SUBVERSION,
                                                     Zoper_PATCH,
                                                     Zoper_TWEAK,
                                                     Zoper_name>
{
public:
    void onInit(haf::scene::AppInitializer& app_initializer) override;
    void onFinish(haf::scene::AppFinisher& app_finisher) override;

};
}  // namespace zoper

#endif
