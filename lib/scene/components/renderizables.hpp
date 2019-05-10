#pragma once

#ifndef LIB_COMPONENT_RENDERIZABLES_INCLUDE_HPP
#define LIB_COMPONENT_RENDERIZABLES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib::scene
{
    class Renderizables : public IComponent
    {
    public:
        Renderizables();
        ~Renderizables() override;

        void update() override;
        
    private:
        class RenderizablesPrivate;
        uptr<RenderizablesPrivate> priv_;
    };
}

#endif
