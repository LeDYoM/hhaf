#include "scenemanager.hpp"
#include "scene.hpp"

#include <lib/system/systemprovider.hpp>
#include <lib/window/i_include/window.hpp>
#include <lib/resources/i_include/resourcemanager.hpp>
#include <lib/render/include/rendertarget.hpp>

#include <lib/include/liblog.hpp>
#include <lib/resources/include/iresourceretriever.hpp>
#include <lib/resources/include/iresourcehandler.hpp>


namespace lib::scene
{
SceneManager::SceneManager(sys::SystemProvider &system_provider)
    : HostedAppService{system_provider}
{
    scene_controller_ = msptr<SceneController>();
    scene_controller_->setSceneManager(this);
}

SceneManager::~SceneManager() = default;

void SceneManager::start()
{
}

void SceneManager::update()
{
    scene_controller_->update();
}

void SceneManager::finish()
{
    scene_controller_->finish();
}

Rectf32 SceneManager::viewPort() const noexcept
{
    return systemProvider().parentWindow().renderTarget()->viewPort();
}

void SceneManager::setViewPort(const Rectf32 &vp) noexcept
{
    systemProvider().parentWindow().renderTarget()->setViewPort(vp);
}

Rectf32 SceneManager::viewRect() const noexcept
{
    return systemProvider().parentWindow().renderTarget()->viewRect();
}

void SceneManager::setViewRect(const Rectf32 &vr) noexcept
{
    systemProvider().parentWindow().renderTarget()->setViewRect(vr);
}

IResourceRetriever &SceneManager::resources()
{
    return systemProvider().resourceManager();
}

IResourceHandler &SceneManager::resourcesLoader()
{
    return systemProvider().resourceManager();
}

} // namespace lib::scene
