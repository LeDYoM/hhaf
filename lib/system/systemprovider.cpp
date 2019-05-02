#include "systemprovider.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include "randomsystem.hpp"
#include "inputsystem.hpp"
#include "simulationsystem.hpp"
#include "filesystem/filesystem.hpp"

#include <backend_dev/include/iwindow.hpp>
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
        window_ = muptr<Window>(app_->getAppDescriptor().wcp);
        input_system_ = muptr<input::InputSystem>(window_->inputDriver());
        scene_manager_ = muptr<scene::SceneManager>(*this);
        resource_manager_ = muptr<core::ResourceManager>(*this);
        random_system_ = muptr<RandomSystem>();
		file_system_ = muptr<FileSystem>(*this);
        simulation_system_ = muptr<SimulationSystem>();
    }

    void SystemProvider::terminate()
    {
        scene_manager_->finish();
        resource_manager_ = nullptr;
        scene_manager_ = nullptr;
        input_system_ = nullptr;
        window_ = nullptr;
        simulation_system_ = nullptr;
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
         return *window_; 
    }

    Window &SystemProvider::parentWindow() noexcept
    {
        return *window_; 
    }
    
    const ResourceManager &SystemProvider::resourceManager() const  noexcept
    {
        return *resource_manager_;
    }
    
    ResourceManager &SystemProvider::resourceManager()  noexcept
    {
        return *resource_manager_;
    }
    
    const input::InputSystem &SystemProvider::inputSystem() const noexcept
    {
        return *input_system_; 
    }

    input::InputSystem &SystemProvider::inputSystem() noexcept
    { 
        return *input_system_;
    }
    
    const RandomSystem &SystemProvider::randomSystem() const noexcept
    {
        return *random_system_;
    }

    RandomSystem &SystemProvider::randomSystem() noexcept
    {
        return *random_system_;
    }

	const FileSystem &SystemProvider::fileSystem() const noexcept
	{
		return *file_system_;
	}

	FileSystem &SystemProvider::fileSystem() noexcept
	{
		return *file_system_;
	}

    const scene::SceneManager &SystemProvider::sceneManager() const noexcept
    {
        return *scene_manager_;
    }
    
    scene::SceneManager &SystemProvider::sceneManager() noexcept
    {
        return *scene_manager_;
    }

    const SimulationSystem & SystemProvider::simulationSystem() const noexcept
    {
        return *simulation_system_;
    }

    SimulationSystem & SystemProvider::simulationSystem() noexcept
    {
        return *simulation_system_;
    }
}
