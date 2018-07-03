#pragma once

#ifndef LIB_COMPONENT_ALIGNED_TEXT_INCLUDE_HPP__
#define LIB_COMPONENT_ALIGNED_TEXT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include "parentrendercomponent.hpp"
#include <lib/scene/scenenodetypes.hpp>
#include <lib/scene/renderizables/nodetext.hpp>


namespace lib::scene
{
    class AlignedTextComponent : public IComponent
    {
    public:
        using BaseClass = IComponent;

        enum class AlignmentX : u8
        {
            Left = 0,
            Center,
            Right
        };

        enum class AlignmentY : u8
        {
            Top = 0,
            Middle,
            Bottom
        };

        AlignedTextComponent() {}
        virtual ~AlignedTextComponent() {}

        PropertyState<AlignmentX> alignmentX;
        PropertyState<AlignmentY> alignmentY;
        PropertyState<Rectf32> alignmentBox;

    protected:
        virtual void update() override final;
    private:
        void updateAlignmentX(const Rectf32 textSize);
        void updateAlignmentY(const Rectf32 textSize);
    };
}

#endif
