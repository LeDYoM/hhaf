#pragma once

#ifndef LIB_COMPONENT_ALIGNED_TEXT_INCLUDE_HPP__
#define LIB_COMPONENT_ALIGNED_TEXT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
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
        PropertyState<vector2df> alignmentSize;

    protected:
        virtual void update() override final;
    private:
        void updateAlignmentX(const f32 textSizeX);
        void updateAlignmentY(const f32 textSizeY);
    };
}

#endif
