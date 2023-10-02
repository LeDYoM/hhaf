HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_UPDATE_NODE_INCLUDE_HPP
#define HAF_SCENE_SCENE_UPDATE_NODE_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::scene
{
enum class SceneUpdateTime : core::u32
{
    UserController = 0U,
    Controller     = 1U,
    UserBeginFrame = 2U,
    BeginFrame     = 3U,
    UserEndFrame   = 4U,
    EndFrame       = 5U,
    UserRender     = 6U,
    Render         = 7U,
    Begin          = UserController,
    End            = Render + 1U,
};

template <typename T>
consteval SceneUpdateTime begin() noexcept
{
    return SceneUpdateTime::Begin;
}

template <typename T>
consteval SceneUpdateTime end() noexcept
{
    return SceneUpdateTime::End;
}

template <typename T>
consteval core::u32 num_begin() noexcept
{
    return static_cast<core::u32>(begin<T>());
}

template <typename T>
consteval core::u32 num_end() noexcept
{
    return static_cast<core::u32>(end<T>());
}

template <typename T>
consteval core::u32 size() noexcept
{
    return num_end<T>();
}

template <typename T>
constexpr SceneUpdateTime toEnum(core::u32 const index) noexcept
{
    return static_cast<T>(index);
}

}  // namespace haf::scene

#endif
