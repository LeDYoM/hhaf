HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_ISCENEMANAGER_SUBSYSTEM_INPUT_SUBSYSTEM_INCLUDE_HPP
#define HAF_SCENE_ISCENEMANAGER_SUBSYSTEM_INPUT_SUBSYSTEM_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>
#include "iscene_manager subsystem.hpp"

namespace haf::scene
{
class InputSubSystem final : public ISceneManagerSubSystem
{
public:
    InputSubSystem();
    virtual bool update(component::ComponentUpdater& component_updater);

private:
    core::str m_subsystem_name;
};
}  // namespace haf::scene

#endif
