#include "systemprovider.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include "randomsystem.hpp"
#include "inputsystem.hpp"

#include <lib/include/backend/iwindow.hpp>
#include <lib/include/core/log.hpp>
#include <lib/include/windowcreationparams.hpp>

#include <lib/core/backendfactory.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::core
{
    void SystemProvider::init(Host& host, const WindowCreationParams& wcp)
    {
        host_ = &host;
        m_window = muptr<Window>(*host_, wcp);
        m_inputSystem = muptr<input::InputSystem>(*host_);
        m_sceneManager = muptr<scene::SceneManager>(*host_, *m_window);
        m_resourceManager = muptr<core::ResourceManager>(*host_);
        random_system_ = muptr<RandomSystem>(*host_);
    }

    void SystemProvider::terminate()
    {
        m_sceneManager->finish();
        m_resourceManager = nullptr;
        m_sceneManager = nullptr;
        m_inputSystem = nullptr;
        m_window = nullptr;
    }

    const core::Host & SystemProvider::host() const noexcept
    {
        return *host_;
    }

    core::Host & SystemProvider::host() noexcept
    {
        return *host_;
    }

    const Window &SystemProvider::parentWindow() const noexcept
    {
         return *m_window; 
    }

    Window &SystemProvider::parentWindow() noexcept
    {
        return *m_window; 
    }
    
    const ResourceManager &SystemProvider::resourceManager() const  noexcept
    {
        return *m_resourceManager;
    }
    
    ResourceManager &SystemProvider::resourceManager()  noexcept
    {
        return *m_resourceManager;
    }
    
    const input::InputSystem &SystemProvider::inputSystem() const noexcept
    {
        return *m_inputSystem; 
    }

    input::InputSystem &SystemProvider::inputSystem() noexcept
    { 
        return *m_inputSystem;
    }
    
    const RandomSystem &SystemProvider::randomSystem() const noexcept
    {
        return *random_system_;
    }

    RandomSystem &SystemProvider::randomSystem() noexcept
    {
        return *random_system_;
    }

    const scene::SceneManager &SystemProvider::sceneManager() const noexcept
    {
        return *m_sceneManager;
    }
    
    scene::SceneManager &SystemProvider::sceneManager() noexcept
    {
        return *m_sceneManager;
    }
}
