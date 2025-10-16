#include <haf/include/render/renderizables.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable_builder.hpp>

using namespace htps;
using namespace haf::scene;

namespace haf::render
{
void Renderizables::setSceneNode(rptr<scene::SceneNode> scene_node) noexcept
{
    m_scene_node = scene_node;
}

sptr<Renderizable> Renderizables::createRenderizable(
    RenderizableBuilderData&& renderizable_builder_data)
{
    auto result{msptr<Renderizable>(
        m_scene_node, core::move(renderizable_builder_data).extract())};
    addRenderizable(result);
    return result;
}

RenderizableBuilder Renderizables::renderizableBuilder()
{
    return RenderizableBuilder{this};
}

void Renderizables::updateRenderizables(
    bool const parent_transformation_changed)
{
    for (auto&& renderizable : m_render_nodes)
    {
        renderizable->render(parent_transformation_changed);
    }
}

void Renderizables::removeRenderizable(sptr<Renderizable> const& element)
{
    LogAsserter::log_assert(element.get() != nullptr,
                            "Received empty renderizable node to be deleted");
    m_render_nodes.erase_values(element);
}

void Renderizables::clearRenderizables()
{
    m_render_nodes.clear();
}

void Renderizables::for_each_node(
    function<void(const sptr<Renderizable>&)> action) const
{
    m_render_nodes.cfor_each(htps::move(action));
}

void Renderizables::addRenderizable(sptr<Renderizable> newElement)
{
    m_render_nodes.push_back(htps::move(newElement));
}

sptr<Renderizable> const& Renderizables::operator[](
    size_type const index) const noexcept
{
    return m_render_nodes[index];
}

size_type Renderizables::size() const
{
    return m_render_nodes.size();
}

bool Renderizables::empty() const noexcept
{
    return m_render_nodes.empty();
}

rptr<scene::SceneNode const> Renderizables::sceneNode() const noexcept
{
    return m_scene_node;
}

}  // namespace haf::render
