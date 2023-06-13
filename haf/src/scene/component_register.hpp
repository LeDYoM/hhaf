HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_COMPONENT_REGISTER_INCLUDE_HPP
#define HAF_SCENE_COMPONENT_REGISTER_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>

namespace haf::scene
{
class SceneManager;

class HAF_PRIVATE ComponentRegister
{
public:
    explicit ComponentRegister(SceneManager& scene_manager);
    bool operator()();
private:
    SceneManager& m_scene_manager;
};
}  // namespace haf::scene

#endif
