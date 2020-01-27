#pragma once

#ifndef LIB_SCENE_SCENE_INCLUDE_HPP
#define LIB_SCENE_SCENE_INCLUDE_HPP

#include "hasname.hpp"
#include "scenenode.hpp"

#include <mtypes/include/types.hpp>
#include <lib/include/core/timepoint.hpp>
#include <lib/scene/components/statescontroller.hpp>

namespace lib
{
class IResourceLoader;
}

namespace lib::scene
{
class SceneManager;

class Scene : public SceneNode
{
public:
    Scene(str name);
    ~Scene() override;

    virtual void onFinished() {}

    inline SceneManager &sceneManager() noexcept { return *m_sceneManager; }
    inline const SceneManager &sceneManager() const noexcept { return *m_sceneManager; }

private:
    SceneManager *m_sceneManager{nullptr};
    friend class SceneController;
};
} // namespace lib::scene

#endif
