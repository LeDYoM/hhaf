#pragma once

#ifndef HAF_SCENE_SCENE_DIRECTOR_HPP
#define HAF_SCENE_SCENE_DIRECTOR_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/function.hpp>

namespace haf::scene
{
/**
 * @brief Type defining the function callback for an scene director
 */
using SceneDirectorType = mtps::function<mtps::str(const mtps::str&)>;
}  // namespace haf::scene

#endif
