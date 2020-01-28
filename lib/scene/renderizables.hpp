#pragma once

#ifndef LIB_COMPONENT_RENDERIZABLES_INCLUDE_HPP
#define LIB_COMPONENT_RENDERIZABLES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/vector.hpp>

#include <lib/scene/renderizable.hpp>

namespace lib::scene
{
class Renderizable;
class SceneNode;

class Renderizables
{
public:
    Renderizables(rptr<SceneNode> scene_node) noexcept
        : scene_node_{std::move(scene_node)} {}

    /// Method to create a Renderizable
    /// @param name The name of the Renderizable node.
    /// @param figure_type Type of the figure to generate.
    /// @param box Box containing the Renderizable.
    /// @param color Color of the Renderizable.
    /// @param num_points Number of points of the Renderizable.
    /// @returns The created Renderizable
    sptr<Renderizable> createRenderizable(
        str name, FigType_t figure_type, Rectf32 box, Color color,
            sptr<ITexture> texture, sptr<IShader> shader, size_type num_points);

    sptr<Renderizable> createRenderizable(str name, FigType_t figure_type)
    {
        return createRenderizable(std::move(name), std::move(figure_type),
        Rectf32{}, colors::White, nullptr, nullptr, 4U);
    }

    sptr<Renderizable> createRenderizable(str name, FigType_t figure_type,
        size_type num_points)
    {
        return createRenderizable(std::move(name), std::move(figure_type),
        Rectf32{}, colors::White, nullptr, nullptr, std::move(num_points));
    }

    sptr<Renderizable> createRenderizable(str name, FigType_t figure_type,
        Rectf32 box, Color color)
    {
        return createRenderizable(std::move(name), std::move(figure_type),
        std::move(box), std::move(color), nullptr, nullptr, 4U);
    }

    sptr<Renderizable> createRenderizable(str name, FigType_t figure_type,
        Rectf32 box, sptr<ITexture> texture)
    {
        return createRenderizable(std::move(name), std::move(figure_type),
        std::move(box), colors::White, std::move(texture), nullptr, 4U);
    }

    sptr<Renderizable> createRenderizable(str name, FigType_t figure_type,
        Rectf32 box)
    {
        return createRenderizable(std::move(name), std::move(figure_type),
        std::move(box), nullptr);
    }

    sptr<Renderizable> createRenderizable(str name, FigType_t figure_type,
        Rectf32 box, Color color, size_type num_points)
    {
        return createRenderizable(std::move(name), std::move(figure_type),
        std::move(box), std::move(color), nullptr, nullptr, 
        std::move(num_points));
    }

    void removeRenderizable(const sptr<Renderizable> &element);
    void clearRenderizables();

    template <typename T>
    constexpr void for_each_node_as(function<void(const sptr<T> &)> action)
    {
        for_each_node([&action](const sptr<Renderizable> &node) {
            if (auto tnode = std::dynamic_pointer_cast<T>(node))
            {
                action(tnode);
            }
        });
    }

    void for_each_node(function<void(const sptr<Renderizable> &)> action) const;

    void updateRenderizables();

private:
    void addRenderizable(sptr<Renderizable> newElement);
    rptr<SceneNode> scene_node_;
    vector<sptr<Renderizable>> render_nodes_;
};
} // namespace lib::scene

#endif
