#ifndef HAF_SCENE_SCENEMETRICS_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>

namespace haf::scene
{
class ISceneMetrics : public ISceneMetricsView
{
public:
    virtual void setViewRect(const htps::Rectf32& new_view) = 0;
    virtual void setViewPort(const htps::Rectf32& new_view_port) = 0;
};
}  // namespace haf::scene

#endif
