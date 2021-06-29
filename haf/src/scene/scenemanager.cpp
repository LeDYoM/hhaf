#include "scenemanager.hpp"
#include "scenecontroller.hpp"

#include <haf/include/scene/scene.hpp>

#include "system/systemprovider.hpp"
#include "window/window.hpp"
#include "resources/resourcemanager.hpp"
#include "render/rendertarget.hpp"

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

bool SceneManager::startScene(const htps::str& scene_name)
{
    return scene_controller_->startScene(scene_name);
}

SceneNodeFactory& SceneManager::sceneNodeFactory()
{
    return scene_controller_->sceneNodeFactory();
}

}  // namespace haf::scene
