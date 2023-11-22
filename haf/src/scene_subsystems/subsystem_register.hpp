HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SUBSYSTEM_REGISTER_INCLUDE_HPP
#define HAF_SCENE_SUBSYSTEM_REGISTER_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>

namespace haf::scene
{
class SceneManagerSubSystemGroup;
class HAF_PRIVATE SubSystemRegister
{
public:
    explicit SubSystemRegister(SceneManagerSubSystemGroup& group);
    bool operator()();

private:
    SceneManagerSubSystemGroup& m_subsystem_group;
};
}  // namespace haf::scene

#endif
