#pragma once

#ifndef LIB_SCENE_SCENENODE_BLOBL_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_BLOBL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <logger/include/log.hpp>

namespace lib::core
{
    class Host;
    class RandomSystem;
}

namespace lib::input
{
    class InputSystem;
}

namespace lib::scene
{
    class SceneNode;

    class SceneNodeBlob
    {
    public:
        SceneNodeBlob(SceneNode& provider);

        const input::InputSystem& inputSystem() const;
        input::InputSystem& inputSystem();

        const core::RandomSystem& randomSystem() const;
        core::RandomSystem& randomSystem();

        Rectf32 scenePerspective() const;

    private:
        SceneNode& scene_node_;
    };
}

#endif
