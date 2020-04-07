#pragma once

#ifndef HAF_SCENE_RENDERDATA_INCLUDE_HPP
#define HAF_SCENE_RENDERDATA_INCLUDE_HPP

namespace haf::scene
{
class ITexture;
class VertexArray;
class Transform;
class IShader;

class RenderData final
{
public:
    constexpr RenderData(
        const VertexArray &va, const Transform &transform,
        const ITexture *texture, const IShader *shader)
        : vArray{va}, transform{transform}, texture{texture}, shader{shader} {}

    const VertexArray &vArray;
    const Transform &transform;
    const ITexture *texture;
    const IShader *shader;
};
} // namespace haf::scene

#endif
