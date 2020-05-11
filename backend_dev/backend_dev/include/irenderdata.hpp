#pragma once

#ifndef HAF_BACKEND_RENDER_DATA_INCLUDE_HPP
#define HAF_BACKEND_RENDER_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/scene/include/vertex.hpp>
#include <haf/scene/include/primitivetype.hpp>
#include "itexture.hpp"
#include "ishader.hpp"

namespace haf::backend
{
struct IRenderData
{
    const scene::Vertex *vertices;
    const mtps::u32 nVertex;
    const scene::PrimitiveType pType;
    const mtps::f32 *transform;
    const ITexture *texture;
    const IShader *shader;
};
} // namespace haf::backend

#endif
