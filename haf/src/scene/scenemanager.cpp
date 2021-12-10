#include "scenemanager.hpp"
#include "scenecontroller.hpp"

#include <haf/include/scene/scene.hpp>

#include "system/systemprovider.hpp"
#include "window/window.hpp"
#include "resources/resourcemanager.hpp"
#include "render/rendertarget.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf::sys;

namespace haf::scene
{
SceneManager::SceneManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider}, scene_controller_{msptr<SceneController>()}
{
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
    return systemProvider().system<Window>().renderTarget()->viewPort();
}

void SceneManager::setViewPort(Rectf32 const& vp)
{
    systemProvider().system<Window>().renderTarget()->setViewPort(vp);
}

Rectf32 SceneManager::currentView() const
{
    return systemProvider().system<Window>().renderTarget()->viewRect();
}

void SceneManager::setViewRect(Rectf32 const& vr)
{
    systemProvider().system<Window>().renderTarget()->setViewRect(vr);
}

sptr<SceneController> const& SceneManager::sceneController() const noexcept
{
    return scene_controller_;
}

sptr<SceneController>& SceneManager::sceneController() noexcept
{
    return scene_controller_;
}

}  // namespace haf::scene
