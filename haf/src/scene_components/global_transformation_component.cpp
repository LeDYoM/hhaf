#include <haf/include/scene_components/global_transformation_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/profiler/code_profiler.hpp>
#include <haf/include/debug_system/debug_types.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/debug_system/idebug_variables.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component_finder.hpp>

#include "system/get_system.hpp"
#include "debug_system/debug_system.hpp"
#include "scene/scene_manager.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace fmath;

namespace haf::scene
{
struct GlobalTransformationComponent::PrivateComponentData
{
    evt::ireceiver m_receiver;
    Matrix4x4 m_transform;
    prop::PropertyState<Matrix4x4> m_localTransformation;
    prop::PropertyState<Matrix4x4> m_parentGlobalTransformation;
};

GlobalTransformationComponent::GlobalTransformationComponent() :
    m_p{make_pimplp<PrivateComponentData>()}
{}

GlobalTransformationComponent::~GlobalTransformationComponent() = default;

void GlobalTransformationComponent::onAttached()
{
    component::ComponentFinder finder{attachedNode()};
    if (auto parentComponent{
            finder.findParentComponent<GlobalTransformationComponent>()};
        parentComponent != nullptr)
    {
        m_p->m_receiver.connect(
            parentComponent, parentComponent->m_globalTransformationChanged,
            make_function(
                this,
                &GlobalTransformationComponent::globalTransformationChanged));
    }
    else
    {
        DisplayLog::verbose("No parent GlobalTransformationComponent found");
    }

    addUpdater({this, &GlobalTransformationComponent::updateMatrix},
               &m_p->m_localTransformation, &m_p->m_parentGlobalTransformation);
    addUpdater({this, &GlobalTransformationComponent::setModelViewMatrix});
}

void GlobalTransformationComponent::localTransformationChanged(
    Matrix4x4 const& localTransform)
{
    m_p->m_localTransformation = localTransform;
}

void GlobalTransformationComponent::globalTransformationChanged(
    Matrix4x4 const& parentMatrix)
{
    m_p->m_parentGlobalTransformation = parentMatrix;
};

void GlobalTransformationComponent::updateMatrix()
{
    m_p->m_transform =
        m_p->m_parentGlobalTransformation() * m_p->m_localTransformation();

/*    if (auto meshRenderContext_{meshRenderContext()};
        !meshRenderContext_.empty())
    {
        meshRenderContext_->modelViewMatrix = m_p->m_transform;
    }
*/
    m_globalTransformationChanged(m_p->m_transform);
}

void GlobalTransformationComponent::setModelViewMatrix()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneRenderContext().setCurrentModelViewMatrix(m_p->m_transform);
}

bool GlobalTransformationComponent::hasPendingMatrixUpdate() const noexcept
{
    return prop::ps_hasChanged(m_p->m_parentGlobalTransformation,
                               m_p->m_localTransformation);
}

}  // namespace haf::scene
