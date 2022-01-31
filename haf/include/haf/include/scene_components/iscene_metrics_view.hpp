#ifndef HAF_SCENE_ISCENEMETRICS_VIEW_INCLUDE_HPP
#define HAF_SCENE_ISCENEMETRICS_VIEW_INCLUDE_HPP

#include <haf/include/types/scene_types.hpp>

namespace haf::scene
{
/**
 * @brief Interface class to read some metrics of the current set
 * @b Scene
 */
class ISceneMetricsView
{
protected:
    virtual ~ISceneMetricsView() = default;
public:
    static constexpr char const StaticTypeName[] = "ISceneMetricsView";

    /**
     * @brief Get the current view set for the Scene
     * @return SceneBox containing the view
     */
    virtual SceneBox currentView() const = 0;

    /**
     * @brief Get The current Viewport of the Scene
     * @return SceneBox Containing the view port
     */
    virtual SceneBox currentViewPort() const = 0;
};

}  // namespace haf::scene

#endif
