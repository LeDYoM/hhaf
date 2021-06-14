#include <haf/include/scene/scenenode.hpp>
#include "scenemanager.hpp"
#include "system/get_system.hpp"

#include <haf/include/render/renderizables.hpp>

using namespace htps;

namespace haf::scene
{
struct SceneNode::SceneNodePrivate
{
    SceneNodePrivate() = default;

    uptr<Renderizables> renderizables;
};

SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    Transformable{},
    sys::DataWrapperCreator{this},
    ComponentContainer{this},
    sys::SystemAccess{parent != nullptr ? &(parent->isystemProvider())
                                        : nullptr},
    InterfaceGetter{this},
    SceneNodeProperties(true),
    p_{make_pimplp<SceneNodePrivate>()}
{}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
    clearComponents();
}

Renderizables& SceneNode::createRenderizables()
{
    LogAsserter::log_assert(
        p_->renderizables == nullptr,
        "createRenderizables already invoked for this object");

    if (p_->renderizables == nullptr)
    {
        p_->renderizables = muptr<Renderizables>(this);
    }

    return renderizables();
}

Renderizables& SceneNode::renderizables()
{
    LogAsserter::log_assert(
        p_->renderizables == nullptr,
        "createRenderizables already invoked for this object");

    return *(p_->renderizables);
}

Renderizables const& SceneNode::renderizables() const
{
    LogAsserter::log_assert(
        p_->renderizables == nullptr,
        "createRenderizables already invoked for this object");

    return *(p_->renderizables);
}

}  // namespace haf::scene
