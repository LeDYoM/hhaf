#include "renderizables.hpp"

#include <lib/include/liblog.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenenode.hpp>

using namespace mtps;

namespace lib::scene
{
sptr<Renderizable> Renderizables::createRenderizable(
    str name,
    FigType_t figure_type,
    Rectf32 box,
    Color color,
    sptr<ITexture> texture,
    sptr<IShader> shader,
    size_type num_points)
{
    auto result(msptr<Renderizable>(
        scene_node_, std::move(name), figure_type, std::move(num_points),
        std::move(box), std::move(color), std::move(texture),
        std::move(shader)));
    addRenderizable(result);
    return result;
}

void Renderizables::updateRenderizables()
{
    for (auto&& renderizable : render_nodes_)
    {
        renderizable->render();
    }
}

void Renderizables::removeRenderizable(const sptr<Renderizable>& element)
{
    log_assert(element.get() != nullptr,
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
    std::for_each(render_nodes_.cbegin(), render_nodes_.cend(), action);
}

void Renderizables::addRenderizable(sptr<Renderizable> newElement)
{
    render_nodes_.push_back(std::move(newElement));
}
}  // namespace lib::scene
