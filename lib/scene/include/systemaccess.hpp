#pragma once

#ifndef LIB_SCENE_SYSTEM_ACCESS_INCLUDE_HPP
#define LIB_SCENE_SYSTEM_ACCESS_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::sys
{
    class ISystemProvider;
}

namespace lib::scene
{
class SceneManager;

class SystemAccess
{
public:
    SystemAccess(rptr<SceneManager> scene_manager);

    const sys::ISystemProvider& isystemProvider() const noexcept;
    sys::ISystemProvider& isystemProvider() noexcept;

private:
    rptr<SceneManager> scene_manager_{nullptr};
    friend class SceneController;
};
} // namespace lib::scene

#endif
