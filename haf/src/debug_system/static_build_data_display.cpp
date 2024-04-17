#include "static_build_data_display.hpp"

#include <haf/include/component/component.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <facil_math/include/matrix4x4.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::debug
{
void logBuildStaticData()
{
    logger::DisplayLog::debug("BuildData: Class sizes:");
    logger::DisplayLog::debug("BuildData: Component: ",
                              sizeof(component::Component));
    logger::DisplayLog::debug("BuildData: ComponentContainer: ",
                              sizeof(component::ComponentContainer));
    logger::DisplayLog::debug("BuildData: SceneNode: ",
                              sizeof(scene::SceneNode));
    logger::DisplayLog::debug("BuildData: Matrix4x4: ",
                              sizeof(fmath::Matrix4x4));
    logger::DisplayLog::debug(
        "BuildData: Matrix4x4 aligned: ",
        sizeof(fmath::Matrix4x4[2]) - sizeof(fmath::Matrix4x4));
}

}  // namespace haf::debug
