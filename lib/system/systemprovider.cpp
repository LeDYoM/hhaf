#include "systemprovider.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include "randomsystem.hpp"
#include "inputsystem.hpp"

#include <lib/include/backend/iwindow.hpp>
#include <lib/include/core/log.hpp>
#include <lib/include/windowcreationparams.hpp>
#include <lib/include/iapp.hpp>

#include <lib/core/backendfactory.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::core
{
    void SystemProvider::init(Host& host, IApp *iapp)
    {
        assert_release(iapp != nullptr, "Cannot create a SystemProvider with a nullptr app");
        host_ = &host;
        app_ = iapp;
        m_window = muptr<Window>(app_->getAppDescriptor().wcp);
        m_inputSystem = muptr<input::InputSystem>(m_window->inputDriver());
        m_sceneManager = muptr<scene::SceneManager>(*this);
        m_resourceManager = muptr<core::ResourceManager>();
        random_system_ = muptr<RandomSystem>();
    }

    void SystemProvider::terminate()
    {
        m_sceneManager->finish();
        m_resourceManager = nullptr;
        m_sceneManager = nullptr;
        m_inputSystem = nullptr;
        m_window = nullptr;
    }

    /*
    const core::Host & SystemProvider::host() const noexcept
    {
        return *host_;
    }

    core::Host & SystemProvider::host() noexcept
    {
        return *host_;
    }
    */

    IApp &SystemProvider::app()
    {
        return *app_;
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
