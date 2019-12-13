#pragma once

#ifndef LIB_SCENE_RENDERDATA_INCLUDE_HPP
#define LIB_SCENE_RENDERDATA_INCLUDE_HPP

namespace lib::scene
{
class Texture;
class VertexArray;
class Transform;
class Shader;

class RenderData final
{
public:
    constexpr RenderData(
        const VertexArray &va, const Transform &transform,
        const Texture *texture, const Shader *shader)
        : vArray{va}, transform{transform}, texture{texture}, shader{shader} {}

    const VertexArray &vArray;
    const Transform &transform;
    const Texture *texture;
    const Shader *shader;
};
} // namespace lib::scene

#endif
