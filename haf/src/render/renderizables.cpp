#include <haf/include/render/renderizables.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/scene/transformable_scene_node.hpp>
#include <haf/include/render/renderizable_builder.hpp>

using namespace htps;
using namespace haf::scene;

namespace haf::render
{
Renderizables::Renderizables(
    rptr<TransformableSceneNode> scene_node) noexcept :
    scene_node_{std::move(scene_node)}
{}

sptr<Renderizable> Renderizables::createRenderizable(
    RenderizableBuilderData&& renderizable_builder_data)
{
    auto result{
        msptr<Renderizable>(scene_node_, renderizable_builder_data.extract())};
    addRenderizable(result);
    return result;
}

RenderizableBuilder Renderizables::renderizableBuilder()
{
    return RenderizableBuilder{this};
}

void Renderizables::updateRenderizables()
{
    for (auto&& renderizable : render_nodes_)
    {
        renderizable->render();
    }
}

void Renderizables::removeRenderizable(sptr<Renderizable> const& element)
{
    LogAsserter::log_assert(element.get() != nullptr,
                            "Received empty renderizable node to be deleted");
    render_nodes_.erase_values(element);
}

void Renderizables::clearRenderizables()
{
    render_nodes_.clear();
}

void Renderizables::for_each_node(
    function<void(const sptr<Renderizable>&)> action) const
{
    render_nodes_.cfor_each(std::move(action));
}

void Renderizables::addRenderizable(sptr<Renderizable> newElement)
{
    render_nodes_.push_back(std::move(newElement));
}

sptr<Renderizable> const& Renderizables::operator[](
    size_type const index) const noexcept
{
    return render_nodes_[index];
}

size_type Renderizables::size() const
{
    return render_nodes_.size();
}

bool Renderizables::empty() const
{
    return render_nodes_.empty();
}

}  // namespace haf::render
