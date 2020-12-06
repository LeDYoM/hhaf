#ifndef HAF_SCENE_SCENEMETRICS_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <haf/scene_components/include/scenemetricsview.hpp>

namespace haf::scene
{
class SceneMetrics : public SceneMetricsView
{
public:
    void setViewRect(const mtps::Rectf32& new_view);
    void setViewPort(const mtps::Rectf32& new_view_port);
};
}  // namespace haf::scene

#endif
