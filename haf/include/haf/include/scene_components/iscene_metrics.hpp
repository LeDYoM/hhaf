#ifndef HAF_SCENE_ISCENEMETRICS_INCLUDE_HPP
#define HAF_SCENE_ISCENEMETRICS_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/scene_components/iscene_metrics_view.hpp>

namespace haf::scene
{
class ISceneMetrics : public ISceneMetricsView
{
    static constexpr char const StaticTypeName[] = "ISceneMetrics";
protected:
    ~ISceneMetrics() override = default;
public:
    virtual void setViewRect(SceneBox const& new_view) = 0;
    virtual void setViewPort(SceneBox const& new_view_port) = 0;

    virtual void move(SceneCoordinates const& delta) = 0;
};

}  // namespace haf::scene

#endif
