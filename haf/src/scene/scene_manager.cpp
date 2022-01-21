#include "scene_manager.hpp"
#include "scene_controller.hpp"

#include <haf/include/scene/scene.hpp>

#include "system/system_provider.hpp"
#include "window/window.hpp"
#include "resources/resource_manager.hpp"
#include "render/render_target.hpp"

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

SceneBox SceneManager::currentViewPort() const
{
    return systemProvider().system<Window>().renderTarget()->viewPort();
}

SceneBox SceneManager::currentView() const
{
    return systemProvider().system<Window>().renderTarget()->viewRect();
}

void SceneManager::setViewPort(SceneBox const& vp)
{
    systemProvider().system<Window>().renderTarget()->setViewPort(vp);
}

void SceneManager::setViewRect(SceneBox const& vr)
{
    systemProvider().system<Window>().renderTarget()->setViewRect(vr);
}

void SceneManager::move(SceneCoordinates const& delta)
{
    setViewRect(currentView() + delta);
}

sptr<SceneController const> SceneManager::sceneController() const noexcept
{
    return scene_controller_;
}

sptr<SceneController> SceneManager::sceneController() noexcept
{
    return scene_controller_;
}

void SceneManager::switchToNextScene()
{
    scene_controller_->switchToNextScene();
}

bool SceneManager::startScene(const htps::str& scene_name)
{
    return scene_controller_->startScene(scene_name);
}

void SceneManager::requestExit()
{
    return scene_controller_->requestExit();
}

bool SceneManager::exitRequested() const
{
    return scene_controller_->exitRequested();
}

SceneNodeFactory& SceneManager::sceneNodeFactory()
{
    return scene_controller_->sceneNodeFactory();
}

bool SceneManager::setNextApp(htps::str const&)
{
    return true;
}

}  // namespace haf::scene
