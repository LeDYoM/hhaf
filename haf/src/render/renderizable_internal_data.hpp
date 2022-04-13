#ifndef HAF_RENDER_RENDERIZABLE_INTERNAL_DATA_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLE_INTERNAL_DATA_INCLUDE_HPP

#include <haf/include/render/renderizable.hpp>

namespace haf::render
{

struct RenderizableInternalData
{
    FigType_t const& figType;
    htps::size_type const& pointCount;
    htps::Rects32 const& textureRect;
};

}  // namespace haf::render

#endif
