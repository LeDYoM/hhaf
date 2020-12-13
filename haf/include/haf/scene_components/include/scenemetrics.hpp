#ifndef HAF_SCENE_SCENEMETRICS_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <haf/scene_components/include/scenemetricsview.hpp>

namespace haf::scene
{
class ISceneMetrics : public ISceneMetricsView
{
public:
    virtual void setViewRect(const mtps::Rectf32& new_view) = 0;
    virtual void setViewPort(const mtps::Rectf32& new_view_port) = 0;
};
}  // namespace haf::scene

#endif
