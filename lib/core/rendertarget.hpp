#pragma once

#ifndef LIB_CORE_RENDER_TARGET_INCLUDE_HPP__
#define LIB_CORE_RENDER_TARGET_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/properties.hpp>

namespace lib
{
    namespace backend
    {
        class IRenderTarget;
    }
    namespace scene
    {
        class RenderData;
    }

    namespace core
    {
        class RenderTarget
        {
        public:
            RenderTarget(backend::IRenderTarget *renderTarget);
            ~RenderTarget();

            PropertyTrigger<Rectf32> viewPort;
            PropertyTrigger<Rectf32> viewRect;

            void draw(const scene::RenderData &renderData);
            void clear();
        private:
            backend::IRenderTarget *m_renderTarget;
        };
    }
}

#endif
