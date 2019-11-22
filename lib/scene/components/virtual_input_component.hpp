#pragma once

#ifndef LIB_VIRTUAL_INPUT_COMPONENT_INCLUDE_HPP
#define LIB_VIRTUAL_INPUT_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/components/input_component_base.hpp>
#include <lib/include/key.hpp>

namespace lib::scene
{
    class VirtualInputComponent : public InputComponentBase
    {
    public:
        VirtualInputComponent();
        ~VirtualInputComponent() override;

        void update() override;

    private:
        virtual void onKeyPressed(const input::Key& key) {}
        virtual void onKeyReleased(const input::Key& key) {}
    };
}

#endif
