#ifndef HAF_EXPORT_DEV_APP_DECLARE_INCLUDE_HPP
#define HAF_EXPORT_DEV_APP_DECLARE_INCLUDE_HPP

#include <hosted_app/include/iapp.hpp>
#include <haf_user/include/iapp_with_default_app_versioning_system.hpp>

#define DECLARE_APP(NAMESPACE, CLASS_NAME)  \
\
namespace NAMESPACE \
{   \
constexpr char const App_name[] = APP_NAME; \
\
class CLASS_NAME final  \
    : public haf::user::IAppWithDefaultVersionSystem<APP_VERSION,       \
                                                     APP_SUBVERSION,    \
                                                     APP_PATCH,         \
                                                     APP_TWEAK,         \
                                                     App_name>          \
{   \
public: \
    void onInit(haf::scene::IAppInitializer& app_initializer) override;  \
    void onFinish(haf::scene::IAppFinisher& app_finisher) override;      \
};  \
}

#endif
