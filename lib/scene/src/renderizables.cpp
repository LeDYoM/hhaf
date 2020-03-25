#include "renderizables.hpp"

#include <lib/include/liblog.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenenode.hpp>

namespace lib::scene
{
mtps::sptr<Renderizable> Renderizables::createRenderizable(
    mtps::str name, FigType_t figure_type, mtps::Rectf32 box, Color color,
    mtps::sptr<ITexture> texture, mtps::sptr<IShader> shader, mtps::size_type num_points)
{
    auto result(mtps::msptr<Renderizable>(
        scene_node_, std::move(name),
        figure_type, std::move(num_points),
        std::move(box), std::move(color),
        std::move(texture), std::move(shader)));
    addRenderizable(result);
    return result;
}

void Renderizables::updateRenderizables()
{
    for (auto &&renderizable : render_nodes_)
    {
        renderizable->render();
    }
}

void Renderizables::removeRenderizable(const mtps::sptr<Renderizable> &element)
{
    log_assert(element.get() != nullptr, "Received empty renderizable node to be deleted");
    render_nodes_.erase_values(element);
}

void Renderizables::clearRenderizables()
{
    render_nodes_.clear();
}

void Renderizables::for_each_node(mtps::function<void(const mtps::sptr<Renderizable> &)> action) const
{
    std::for_each(render_nodes_.cbegin(), render_nodes_.cend(), action);
}

void Renderizables::addRenderizable(mtps::sptr<Renderizable> newElement)
{
    render_nodes_.push_back(std::move(newElement));
}
} // namespace lib::scene
