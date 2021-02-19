#ifndef HAF_SCENE_SCENEMANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <system/i_include/systembase.hpp>
#include <haf/scene_components/include/scenemetrics.hpp>

namespace haf::scene
{
class SceneController;
}  // namespace haf::scene

namespace haf::scene
{
class SceneManager final : public sys::SystemBase, public ISceneMetrics
{
public:
    explicit SceneManager(sys::SystemProvider& system_provider);
    ~SceneManager();

    void start();
    void update();
    void finish();

    htps::Rectf32 currentViewPort() const override;
    htps::Rectf32 currentView() const override;
    void setViewPort(const htps::Rectf32& vp) override;
    void setViewRect(const htps::Rectf32& vr) override;

    htps::sptr<SceneController> const& sceneController() const noexcept;
    htps::sptr<SceneController>& sceneController() noexcept;

private:
    htps::sptr<SceneController> scene_controller_;
};
}  // namespace haf::scene

#endif
