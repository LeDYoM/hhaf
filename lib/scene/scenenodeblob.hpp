#pragma once

#ifndef LIB_SCENE_SCENENODE_BLOBL_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_BLOBL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

namespace lib
{
    class IApp;
    class IResourceLoader;
}

namespace lib::sys
{
    class RandomSystem;
    class InputSystem;
}

namespace lib::scene
{
    class SceneNode;
    class SceneManager;
    class SceneController;

    class SceneNodeBlob
    {
    public:
        SceneNodeBlob(SceneNode& provider);

        const SceneManager &sceneManager() const noexcept;
        SceneManager &sceneManager() noexcept;

        const SceneController &sceneController() const noexcept;
        SceneController &sceneController() noexcept;

        const sys::InputSystem& inputSystem() const noexcept;
        sys::InputSystem& inputSystem() noexcept;

        const sys::RandomSystem& randomSystem() const noexcept;
        sys::RandomSystem& randomSystem() noexcept;

        const IApp& app() const;
        IApp& app();

        template <typename T>
        T &app() { return (static_cast<T&>(app())); }

        Rectf32 scenePerspective() const;

       void loadResources(IResourceLoader &&resourceloader);
 
    private:
        SceneNode& scene_node_;
    };
}

#endif
