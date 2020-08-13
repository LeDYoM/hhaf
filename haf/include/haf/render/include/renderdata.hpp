#pragma once

#ifndef HAF_SCENE_RENDERDATA_INCLUDE_HPP
#define HAF_SCENE_RENDERDATA_INCLUDE_HPP

namespace haf::scene
{
class Matrix4x4;
class VertexArray;
}  // namespace haf::scene

namespace haf::res
{
class ITexture;
class IShader;
}  // namespace haf::res

namespace haf::scene
{
class RenderData final
{
public:
    constexpr RenderData(const VertexArray& va,
                         const Matrix4x4& transform,
                         const res::ITexture* texture,
                         const res::IShader* shader) :
        vArray{va}, transform{transform}, texture{texture}, shader{shader}
    {}

    const VertexArray& vArray;
    const Matrix4x4& transform;
    const res::ITexture* texture;
    const res::IShader* shader;
};
}  // namespace haf::scene

#endif
