#pragma once

#ifndef HAF_SCENE_SCENEMANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/rect.hpp>

#include <haf/system/include/appservice.hpp>

namespace haf
{
class IResourceRetriever;
class IResourceHandler;
} // namespace haf

namespace haf::scene
{
class Scene;
class SceneController;
}

namespace haf::scene
{
class SceneManager : public AppService
{
public:
    SceneManager(sys::SystemProvider &system_provider);
    ~SceneManager() override;

    void start();
    void update();
    void finish();

    IResourceRetriever &resources();
    IResourceHandler &resourcesLoader();

    mtps::Rectf32 viewPort() const noexcept;
    void setViewPort(const mtps::Rectf32 &vp) noexcept;
    mtps::Rectf32 viewRect() const noexcept;
    void setViewRect(const mtps::Rectf32 &vr) noexcept;

    inline const mtps::sptr<SceneController> &sceneController() const
        noexcept { return scene_controller_; }

    inline mtps::sptr<SceneController> &sceneController() noexcept { return scene_controller_; }

private:
    mtps::sptr<SceneController> scene_controller_;
};
} // namespace haf::scene

#endif
