#include <haf/include/scene_components/global_transformation_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/profiler/code_profiler.hpp>
#include <haf/include/debug_system/debug_types.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/debug_system/idebug_variables.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component_finder.hpp>
#include <haf/include/scene_components/scene_render_properties_component.hpp>

#include "system/get_system.hpp"
#include "debug_system/debug_system.hpp"
#include "scene/scene_manager.hpp"

#include <hlog/include/hlog.hpp>

using namespace haf::core;
using namespace haf::math;

namespace haf::scene
{
struct GlobalTransformationComponent::ComponentsRequired
{
    sptr<haf::scene::SceneRenderPropertiesComponent> m_scene_render_properties;
};

struct GlobalTransformationComponent::PrivateComponentData
{
    evt::ireceiver m_receiver;
    Matrix4x4 m_transform;
    prop::PropertyState<Matrix4x4> m_localTransformation_copy;
    prop::PropertyState<Matrix4x4> m_parentGlobalTransformation;
};

GlobalTransformationComponent::GlobalTransformationComponent() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

GlobalTransformationComponent::~GlobalTransformationComponent() = default;

bool GlobalTransformationComponent::addRequirements(
    component::ComponentRequirements& component_requirements)
{
    bool isOk{true};
    isOk &= component_requirements.getOrCreateComponent(
        m_components->m_scene_render_properties);
    return isOk;
}

void GlobalTransformationComponent::onAttached()
{
    connectToParentGlobalTransformationChanged();

    addUpdater({this, &GlobalTransformationComponent::updateMatrix},
               &m_p->m_localTransformation_copy,
               &m_p->m_parentGlobalTransformation);
    addUpdater({this, &GlobalTransformationComponent::setModelViewMatrix});
}

void GlobalTransformationComponent::connectToParentGlobalTransformationChanged()
{
    auto const node_name = attachedNode()->name();
    (void)(node_name);

    component::ComponentFinder finder{attachedNode()};
    if (auto parentComponent{
            finder.findParentComponent<GlobalTransformationComponent>()};
        parentComponent != nullptr)
    {
        m_p->m_receiver.shared_connect(
            parentComponent, parentComponent->m_globalTransformationChanged,
            make_function(
                this,
                &GlobalTransformationComponent::globalTransformationChanged));
    }
    else
    {
        logger::DisplayLog::verbose(
            "No parent GlobalTransformationComponent found");
    }
}

void GlobalTransformationComponent::localTransformationChanged(
    Matrix4x4 const& localTransform)
{
    m_p->m_localTransformation_copy = localTransform;
}

void GlobalTransformationComponent::globalTransformationChanged(
    Matrix4x4 const& parentMatrix)
{
    m_p->m_parentGlobalTransformation = parentMatrix;
};

void GlobalTransformationComponent::updateMatrix()
{
    auto const node_name = attachedNode()->name();
    (void)(node_name);

    m_p->m_transform =
        m_p->m_parentGlobalTransformation() * m_p->m_localTransformation_copy();

    m_globalTransformationChanged(m_p->m_transform);
}

void GlobalTransformationComponent::setModelViewMatrix()
{
    m_components->m_scene_render_properties->setModelMatrix(m_p->m_transform);
}

bool GlobalTransformationComponent::hasPendingMatrixUpdate() const noexcept
{
    return prop::ps_hasChanged(m_p->m_parentGlobalTransformation,
                               m_p->m_localTransformation_copy);
}

}  // namespace haf::scene
