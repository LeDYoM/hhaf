#include "static_build_data_display.hpp"

#include <haf/include/component/component.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <facil_math/include/matrix4x4.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::debug
{
void logBuildStaticData()
{
    DisplayLog::debug("BuildData: Class sizes:");
    DisplayLog::debug("BuildData: Component: ", sizeof(component::Component));
    DisplayLog::debug("BuildData: ComponentContainer: ",
                      sizeof(component::ComponentContainer));
    DisplayLog::debug("BuildData: SceneNode: ", sizeof(scene::SceneNode));
    DisplayLog::debug("BuildData: Matrix4x4: ", sizeof(fmath::Matrix4x4));
    DisplayLog::debug("BuildData: Matrix4x4 aligned: ",
                      sizeof(fmath::Matrix4x4[2]) - sizeof(fmath::Matrix4x4));
}

}  // namespace haf::debug
