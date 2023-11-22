#include "haf_app_middleware.hpp"

#include <haf/include/scene_components/iapp_finisher.hpp>
#include <haf/include/scene_components/iapp_initializer.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;

namespace haf::app_middleware
{
void HafAppMiddleware::onInit(IAppInitializer& app_initializer)
{
    (void)(app_initializer);
    logger::DisplayLog::verbose("Initializing HafAppFirmware");
}

void HafAppMiddleware::onFinish(IAppFinisher&)
{
}

}  // namespace haf::app_middleware
