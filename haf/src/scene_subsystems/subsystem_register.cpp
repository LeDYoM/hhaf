#include "subsystem_register.hpp"
#include "scene_manager subsystem_group.hpp"
#include "input_subsystem.hpp"
#include "view_updater_subsystem.hpp"
#include "internal_controller_subsystem.hpp"
#include "local_view_updater_subsystem.hpp"
#include "global_view_updater_subsystem.hpp"
#include "material_updater_subsystem.hpp"
#include "render_subsystem.hpp"

namespace haf::scene
{
SubSystemRegister::SubSystemRegister(SceneManagerSubSystemGroup& group) :
    m_subsystem_group{group}
{}

bool SubSystemRegister::operator()()
{
    bool ok{true};
    m_subsystem_group.add(core::muptr<InputSubSystem>());
    m_subsystem_group.add(core::muptr<InternalControllerSubSystem>());
    m_subsystem_group.add(core::muptr<ViewUpdaterSubSystem>());
    m_subsystem_group.add(core::muptr<LocalViewUpdaterSubSystem>());
    m_subsystem_group.add(core::muptr<GlobalViewUpdaterSubSystem>());
    m_subsystem_group.add(core::muptr<MaterialUpdaterSubSystem>());
    m_subsystem_group.add(core::muptr<RenderSubSystem>());
    return ok;
}

}  // namespace haf::scene
