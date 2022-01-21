#ifndef HAF_SCENE_RENDERDATA_INCLUDE_HPP
#define HAF_SCENE_RENDERDATA_INCLUDE_HPP

namespace haf::backend
{
struct IRenderData;
}

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
    constexpr RenderData(
        VertexArray const& va,
        scene::Matrix4x4 const& transform,
        res::ITexture const* const texture,
        res::IShader const* const shader,
        backend::IRenderData const* const irender_data = nullptr) noexcept :
        vArray{va},
        transform{transform},
        texture{texture},
        shader{shader},
        irender_data{irender_data}
    {}

    VertexArray const& vArray;
    scene::Matrix4x4 const& transform;
    res::ITexture const* texture;
    res::IShader const* shader;
    backend::IRenderData const* const irender_data;
};
}  // namespace haf::render

#endif
