#ifndef HAF_SCENE_SCENEMANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <haf/include/scene_components/scenemetrics.hpp>
#include "system/systembase.hpp"

namespace haf::scene
{
class SceneController;
}  // namespace haf::scene

namespace haf::scene
{
class SceneManager final : public sys::SystemBase
{
public:
    explicit SceneManager(sys::SystemProvider& system_provider);
    ~SceneManager();

    void start();
    void update();
    void finish();

    htps::Rectf32 currentViewPort() const;
    htps::Rectf32 currentView() const;
    void setViewPort(const htps::Rectf32& vp);
    void setViewRect(const htps::Rectf32& vr);

    htps::sptr<SceneController> const& sceneController() const noexcept;
    htps::sptr<SceneController>& sceneController() noexcept;

private:
    htps::sptr<SceneController> scene_controller_;
};
}  // namespace haf::scene

#endif
