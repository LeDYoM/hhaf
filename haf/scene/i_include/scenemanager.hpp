#pragma once

#ifndef HAF_SCENE_SCENEMANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

#include <system/i_include/systembase.hpp>

namespace haf
{
class IResourceRetriever;
class IResourceHandler;
}  // namespace haf

namespace haf::scene
{
class Scene;
class SceneController;
}  // namespace haf::scene

namespace haf::scene
{
class SceneManager : public sys::SystemBase
{
public:
    SceneManager(sys::SystemProvider& system_provider);
    ~SceneManager();

    void start();
    void update();
    void finish();

    IResourceRetriever& resources();
    IResourceHandler& resourcesLoader();

    mtps::Rectf32 viewPort() const;
    void setViewPort(const mtps::Rectf32& vp);
    mtps::Rectf32 viewRect() const;
    void setViewRect(const mtps::Rectf32& vr);

    const mtps::sptr<SceneController>& sceneController() const noexcept;
    mtps::sptr<SceneController>& sceneController() noexcept;

private:
    mtps::sptr<SceneController> scene_controller_;
};
}  // namespace haf::scene

#endif
