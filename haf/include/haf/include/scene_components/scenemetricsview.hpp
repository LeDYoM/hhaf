#ifndef HAF_SCENE_ISCENEMETRICS_VIEW_INCLUDE_HPP
#define HAF_SCENE_ISCENEMETRICS_VIEW_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

namespace haf::scene
{
/**
 * @brief Interface class to read some metrics of the current set
 * @b Scene
 */
class ISceneMetricsView
{
public:
    /**
     * @brief Destroy the ISceneMetricsView object
     * Default empty destructor.
     */
    ~ISceneMetricsView() {}

    /**
     * @brief Get the current view set for the Scene
     * @return htps::Rectf32 containing the view
     */
    virtual htps::Rectf32 currentView() const = 0;

    /**
     * @brief Get The current Viewport of the Scene
     * @return htps::Rectf32 Containing the view port
     */
    virtual htps::Rectf32 currentViewPort() const = 0;
};
}  // namespace haf::scene

#endif
