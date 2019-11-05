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

namespace lib::core
{
    class RandomSystem;
}

namespace lib::input
{
    class InputSystem;
}

namespace lib::scene
{
    class SceneNode;
    class SceneManager;

    class SceneNodeBlob
    {
    public:
        SceneNodeBlob(SceneNode& provider);

        const SceneManager &sceneManager() const noexcept;
        SceneManager &sceneManager() noexcept;

        const input::InputSystem& inputSystem() const noexcept;
        input::InputSystem& inputSystem() noexcept;

        const core::RandomSystem& randomSystem() const noexcept;
        core::RandomSystem& randomSystem() noexcept;

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
