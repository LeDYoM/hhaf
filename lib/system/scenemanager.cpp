#include "scenemanager.hpp"

#include <lib/system/systemprovider.hpp>
#include <lib/system/window.hpp>
#include <lib/system/resourcemanager.hpp>
#include <lib/system/rendertarget.hpp>

#include <lib/include/liblog.hpp>
#include <lib/include/resources/iresourceretriever.hpp>

namespace lib::scene
{
SceneManager::SceneManager(core::SystemProvider &system_provider)
    : HostedAppService{system_provider}
{
    scene_controller_ = m_componentContainer.addComponentOfType<SceneController>();
    scene_controller_->setSceneManager(this);
}

SceneManager::~SceneManager() = default;

void SceneManager::start()
{
}

void SceneManager::update()
{
    m_componentContainer.updateComponents();
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
} // namespace lib::scene
