#pragma once

#ifndef LIB_COMPONENT_RENDERIZABLES_INCLUDE_HPP
#define LIB_COMPONENT_RENDERIZABLES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/vector.hpp>

#include <lib/scene/icomponent.hpp>

#include <lib/scene/renderizables/renderizable.hpp>

namespace lib::scene
{
class Renderizable;

class Renderizables : public IComponent
{
public:
    /// Method to create a Renderizable
    /// @param name The name of the Renderizable node.
    /// @param figure_type Type of the figure to generate.
    /// @param box Box containing the Renderizable.
    /// @param color Color of the Renderizable.
    /// @param num_points Number of points of the Renderizable.
    /// @returns The created Renderizable
    sptr<Renderizable> createRenderizable(
        str name, FigType_t figure_type, Rectf32 box = Rectf32{},
        Color color = colors::White, size_type num_points = 4U);

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

    void postUpdate() override;

private:
    void addRenderizable(sptr<Renderizable> newElement);
    vector<sptr<Renderizable>> render_nodes_;
};
} // namespace lib::scene

#endif
