#ifndef HAF_SCENE_SCENEMETRICS_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/system/idatawrapper.hpp>

#include <haf/include/scene_components/scenemetricsview.hpp>

namespace haf::scene
{
class HAF_API SceneMetrics : public SceneMetricsView
{
    using BaseClass                              = SceneMetricsView;
    static constexpr char const StaticTypeName[] = "SceneMetrics";

public:
    void setViewRect(SceneBox const& new_view);
    void setViewPort(SceneBox const& new_view_port);

    void move(SceneCoordinates const& delta);
};
}  // namespace haf::scene

#endif
