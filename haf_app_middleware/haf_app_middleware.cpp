#include "haf_app_middleware.hpp"

#include <haf/include/scene_components/app_finisher.hpp>
#include <haf/include/scene_components/app_initializer.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;

namespace haf::app_middleware
{
HafAppMiddleware::HafAppMiddleware()  = default;
HafAppMiddleware::~HafAppMiddleware() = default;

void HafAppMiddleware::onInit(AppInitializer& app_initializer)
{
    (void)(app_initializer);
    DisplayLog::verbose("Initializing HafAppFirmware");
}

void HafAppMiddleware::onHostInit(host::HostCommunication&)
{}

}  // namespace haf::app_middleware
