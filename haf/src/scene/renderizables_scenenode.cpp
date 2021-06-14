#include <haf/include/scene/renderizables_scenenode.hpp>
#include "scenemanager.hpp"
#include "system/get_system.hpp"

#include <haf/include/render/renderizables.hpp>

using namespace htps;

namespace haf::scene
{
struct RenderizablesSceneNode::RenderizablesSceneNodePrivate
{
    RenderizablesSceneNodePrivate() = default;

    uptr<Renderizables> renderizables;
};

RenderizablesSceneNode::RenderizablesSceneNode(rptr<SceneNode> parent,
                                               str name) :
    BaseClass{parent, std::move(name)},
    p_{make_pimplp<RenderizablesSceneNodePrivate>()}
{}

RenderizablesSceneNode::~RenderizablesSceneNode() = default;

Renderizables& RenderizablesSceneNode::createRenderizables()
{
    LogAsserter::log_assert(
        !containsRenderizables(),
        "createRenderizables already invoked for this object");

    if (p_->renderizables == nullptr)
    {
        p_->renderizables = muptr<Renderizables>(this);
    }

    return renderizables();
}

Renderizables& RenderizablesSceneNode::renderizables()
{
    LogAsserter::log_assert(
        containsRenderizables(),
        "createRenderizables is not invoked for this object");

    return *(p_->renderizables);
}

Renderizables const& RenderizablesSceneNode::renderizables() const
{
    LogAsserter::log_assert(
        containsRenderizables(),
        "createRenderizables is not invoked for this object");

    return *(p_->renderizables);
}

bool RenderizablesSceneNode::containsRenderizables() const noexcept
{
    return p_->renderizables != nullptr;
}

}  // namespace haf::scene
