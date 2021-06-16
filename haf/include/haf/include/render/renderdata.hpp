#ifndef HAF_SCENE_RENDERDATA_INCLUDE_HPP
#define HAF_SCENE_RENDERDATA_INCLUDE_HPP

namespace haf::scene
{
class Matrix4x4;
}  // namespace haf::scene

namespace haf::res
{
class ITexture;
class IShader;
}  // namespace haf::res

namespace haf::render
{
class VertexArray;

class RenderData final
{
public:
    constexpr RenderData(VertexArray const& va,
                         scene::Matrix4x4 const& transform,
                         res::ITexture const * const texture,
                         res::IShader const * const shader) :
        vArray{va}, transform{transform}, texture{texture}, shader{shader}
    {}

    VertexArray const& vArray;
    scene::Matrix4x4 const& transform;
    res::ITexture const * texture;
    res::IShader const * shader;
};
}  // namespace haf::scene

#endif
