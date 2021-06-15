#include <haf/include/scene/renderizables_scenenode.hpp>
#include "scenemanager.hpp"
#include "system/get_system.hpp"

#include <haf/include/render/renderizables.hpp>

using namespace htps;

namespace haf::scene
{
struct RenderizablesSceneNode::RenderizablesSceneNodePrivate
{
    RenderizablesSceneNodePrivate(rptr<RenderizablesSceneNode> _this)
    {
        renderizables = muptr<Renderizables>(_this);
    }

    uptr<Renderizables> renderizables;
};

RenderizablesSceneNode::RenderizablesSceneNode(rptr<SceneNode> parent,
                                               str name) :
    BaseClass{parent, std::move(name)},
    p_{make_pimplp<RenderizablesSceneNodePrivate>(this)}
{}

RenderizablesSceneNode::~RenderizablesSceneNode() = default;

Renderizables& RenderizablesSceneNode::renderizables() noexcept
{
    return *(p_->renderizables);
}

Renderizables const& RenderizablesSceneNode::renderizables() const noexcept
{
    return *(p_->renderizables);
}

}  // namespace haf::scene
