#pragma once

#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/function.hpp>

#include <lib/system/appservice.hpp>

#include <lib/scene/scenecontroller.hpp>

namespace lib
{
    class IResourceRetriever;
    class IResourceHandler;
}

namespace lib::scene
{
    class Scene;
}

namespace lib::scene
{
class SceneManager : public HostedAppService
{
public:
    SceneManager(sys::SystemProvider &system_provider);
    ~SceneManager() override;

    void start();
    void update();
    void finish();

    IResourceRetriever &resources();
    IResourceHandler &resourcesLoader();

    Rectf32 viewPort() const noexcept;
    void setViewPort(const Rectf32 &vp) noexcept;
    Rectf32 viewRect() const noexcept;
    void setViewRect(const Rectf32 &vr) noexcept;

    inline const sptr<SceneController> &sceneController() const
        noexcept { return scene_controller_; }

    inline sptr<SceneController> &sceneController() noexcept { return scene_controller_; }

private:
    sptr<SceneController> scene_controller_;
};
} // namespace lib::scene

#endif
