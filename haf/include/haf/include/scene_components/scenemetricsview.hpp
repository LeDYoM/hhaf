#ifndef HAF_SCENE_SCENEMETRICS_VIEW_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_VIEW_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/system/idatawrapper.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

namespace haf::scene
{
/**
 * @brief Interface class to read some metrics of the current set
 * @b Scene
 */
class SceneMetricsView : public sys::IDataWrapper
{
public:
    /**
     * @brief Get the current view set for the Scene
     * @return htps::Rectf32 containing the view
     */
    htps::Rectf32 currentView() const;

    /**
     * @brief Get The current Viewport of the Scene
     * @return htps::Rectf32 Containing the view port
     */
    htps::Rectf32 currentViewPort() const;
};

}  // namespace haf::scene

#endif
