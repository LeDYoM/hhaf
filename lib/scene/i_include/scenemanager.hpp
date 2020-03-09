#pragma once

#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/rect.hpp>

#include <lib/system/include/appservice.hpp>

namespace lib
{
class IResourceRetriever;
class IResourceHandler;
} // namespace lib

namespace lib::scene
{
class Scene;
class SceneController;
}

namespace lib::scene
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
