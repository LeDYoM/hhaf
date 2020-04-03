#pragma once

#ifndef LIB_BACKEND_RENDER_DATA_INCLUDE_HPP
#define LIB_BACKEND_RENDER_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/vertex.hpp>
#include <lib/scene/include/vertexarray.hpp>
#include "itexture.hpp"
#include "ishader.hpp"

namespace lib::backend
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
} // namespace lib::backend

#endif
