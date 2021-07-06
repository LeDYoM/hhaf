#ifndef HAF_SCENE_SCENEMETRICS_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/system/idatawrapper.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>

namespace haf::scene
{
class HAF_API SceneMetrics : public SceneMetricsView
{
public:
    void setViewRect(htps::Rectf32 const& new_view);
    void setViewPort(htps::Rectf32 const& new_view_port);
};
}  // namespace haf::scene

#endif
