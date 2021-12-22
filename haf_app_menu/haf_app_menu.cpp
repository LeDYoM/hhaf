#include "haf_app_menu.hpp"

#include <haf/include/scene_components/iapp_finisher.hpp>
#include <haf/include/scene_components/iapp_initializer.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;

namespace haf::app_menu
{

void HafAppMenu::onInit(IAppInitializer& app_initializer)
{
    (void)(app_initializer);
    DisplayLog::verbose("Initializing HafAppMenu");
}

void HafAppMenu::onFinish(IAppFinisher& finisher)
{
    finisher.setNextApp("Zoper");
}

}  // namespace haf::app_menu
