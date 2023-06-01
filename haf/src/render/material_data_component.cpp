#include <haf/include/render/material_data_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/scene_components/global_transformation_component.hpp>

#include "system/get_system.hpp"
#include "resources/resource_manager.hpp"
#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/scene_components/transformation_component.hpp>

using namespace haf::core;

namespace haf::render
{
struct MaterialDataComponent::ComponentsRequired
{
};

struct MaterialDataComponent::PrivateComponentData
{
};

MaterialDataComponent::MaterialDataComponent() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

MaterialDataComponent::~MaterialDataComponent() = default;

bool MaterialDataComponent::addRequirements(
    component::ComponentRequirements& /*component_requirements*/)
{
    bool isOk{true};
    return isOk;
}

void MaterialDataComponent::onAttached()
{
}

}  // namespace haf::render
