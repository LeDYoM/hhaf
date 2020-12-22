#include "haf_app_menu.hpp"

#include <mtypes/include/serializer.hpp>
#include <haf/filesystem/include/fileserializer.hpp>
#include <haf/scene_components/include/scenemetrics.hpp>
#include <haf/scene_components/include/scenefactory.hpp>
#include <haf/scene_components/include/scenecontrol.hpp>
#include <haf/shareddata/include/shareddata.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::scene;

namespace haf::app_menu
{

void HafAppMenu::configureScenes(haf::sys::DataWrapperCreator&)
{}

HafAppMenu::HafAppMenu()  = default;
HafAppMenu::~HafAppMenu() = default;

void HafAppMenu::onInit(SceneGroupInitializer& scene_group_initializer)
{
    DisplayLog::verbose("Initializing HafAppMenu");

    //    configureScenes(data_wrapper_creator);
}

void HafAppMenu::onFinish(haf::sys::DataWrapperCreator&)
{}

}  // namespace haf::app_menu
