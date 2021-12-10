#ifndef HAF_SCENE_SCENEMANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <haf/include/scene_components/scenemetrics.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>
#include "system/systembase.hpp"

namespace haf::scene
{
class SceneController;
class SceneNode;
}  // namespace haf::scene

namespace haf::scene
{
class SceneManager final : public sys::SystemBase, public ISceneMetricsView
{
public:
    explicit SceneManager(sys::SystemProvider& system_provider);
    ~SceneManager();

    void start();
    void update();
    void finish();

    SceneBox currentView() const override;
    SceneBox currentViewPort() const override;
    void setViewPort(htps::Rectf32 const& vp);
    void setViewRect(htps::Rectf32 const& vr);

    htps::sptr<SceneController> const& sceneController() const noexcept;
    htps::sptr<SceneController>& sceneController() noexcept;

private:
    htps::sptr<SceneController> scene_controller_;
};
}  // namespace haf::scene

#endif
