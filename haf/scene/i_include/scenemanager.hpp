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

    mtps::Rectf32 currentViewPort() const override;
    mtps::Rectf32 currentView() const override;
    void setViewPort(const mtps::Rectf32& vp) override;
    void setViewRect(const mtps::Rectf32& vr) override;

    mtps::sptr<SceneController> const& sceneController() const noexcept;
    mtps::sptr<SceneController>& sceneController() noexcept;

private:
    mtps::sptr<SceneController> scene_controller_;
};
}  // namespace haf::scene

#endif
