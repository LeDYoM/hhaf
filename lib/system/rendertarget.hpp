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
            RenderTarget(rawptr<backend::IRenderTarget> renderTarget);
            ~RenderTarget();

            void setViewPort(const Rectf32 &nviewport);
            Rectf32 viewPort() const;
            void setViewRect(const Rectf32 &nviewRect);
            Rectf32 viewRect() const;

            void draw(const scene::RenderData &renderData);
            void clear();
        private:
            rawptr<backend::IRenderTarget> m_renderTarget;
        };
    }
}

#endif
