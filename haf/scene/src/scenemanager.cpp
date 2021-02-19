#include <haf/scene/i_include/scenemanager.hpp>
#include <haf/scene/include/scene.hpp>

#include <system/i_include/systemprovider.hpp>
#include <window/i_include/window.hpp>
#include <scene/i_include/scenecontroller.hpp>
#include <resources/i_include/resourcemanager.hpp>
#include <render/i_include/rendertarget.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene
{
SceneManager::SceneManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider}
{
    scene_controller_ = msptr<SceneController>();
    scene_controller_->setSceneManager(this);
}

SceneManager::~SceneManager() = default;

void SceneManager::start()
{}

void SceneManager::update()
{
    scene_controller_->update();
}

void SceneManager::finish()
{
    scene_controller_->finish();
}

Rectf32 SceneManager::currentViewPort() const
{
    return systemProvider().parentWindow().renderTarget()->viewPort();
}

void SceneManager::setViewPort(const Rectf32& vp)
{
    systemProvider().parentWindow().renderTarget()->setViewPort(vp);
}

Rectf32 SceneManager::currentView() const
{
    return systemProvider().parentWindow().renderTarget()->viewRect();
}

void SceneManager::setViewRect(const Rectf32& vr)
{
    systemProvider().parentWindow().renderTarget()->setViewRect(vr);
}

const sptr<SceneController>& SceneManager::sceneController() const noexcept
{
    return scene_controller_;
}

sptr<SceneController>& SceneManager::sceneController() noexcept
{
    return scene_controller_;
}

}  // namespace haf::scene
