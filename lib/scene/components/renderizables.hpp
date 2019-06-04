#pragma once

#ifndef LIB_COMPONENT_RENDERIZABLES_INCLUDE_HPP
#define LIB_COMPONENT_RENDERIZABLES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/components/icomponent.hpp>

#include <lib/scene/renderizables/renderizable.hpp>

namespace lib::scene
{
    class Renderizable;

    class Renderizables : public IComponent
    {
    public:
        Renderizables();
        ~Renderizables() override;

        void update() override final;

        void onAttached() override;

        /**
        * Method to add a user defined renderizable
        * @params args Arguments to be passed to the constructor
        * @returns The created renderizable
        */
        template <typename T, typename... Args>
        sptr<T> createRenderizable(Args&&... args)
        {
            auto result(msptr<T>(attachedNode(), std::forward<Args>(args)...));
            addRenderizable(result);
            return result;
        }

        sptr<Renderizable> createNode(const str& name)
        {
            auto result(msptr<Renderizable>(attachedNode(), name, 0U));
            addRenderizable(result);
            return result;
        }

        void removeRenderizable(sptr<Renderizable> element);
        void clearRenderizables();

        template <typename T>
        constexpr void for_each_node_as(function<void(const sptr<T> &)> action)
        {
            for_each_node([&action](const sptr<Renderizable>&node) {
                if (auto tnode = std::dynamic_pointer_cast<T>(node)) {
                    action(tnode);
                }
            });
        }

        void for_each_node(function<void(const sptr<Renderizable> &)> action) const;

        void postUpdate();

    private:
        void addRenderizable(sptr<Renderizable> newElement);

        class RenderizablesPrivate;
        uptr<RenderizablesPrivate> priv_;
    };
}

#endif
