HAF_PRAGMA_ONCE
#ifndef HAF_RESOURCES_SHADER_SHADER_METADATA_INCLUDE_HPP
#define HAF_RESOURCES_SHADER_SHADER_METADATA_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/resources/shader_code.hpp>
#include <haf/include/resources/iresource.hpp>
#include <haf/include/resources/vertex_buffer_object.hpp>
#include <facil_math/include/matrix4x4.hpp>

namespace haf::res
{
class ShaderMetadata final
{
public:
    static constexpr const haf::core::str_view StaticTypeName{"ShaderMetadata"};

    ShaderMetadata();
    ~ShaderMetadata();

    core::u32 numAttribs() const;
    render::VertexFormat vertexFormat(core::u32 const index) const;

    core::s32 attributeIndex(core::str_view const name) const;
    render::VertexFormat attributeFormat(core::u32 const attributeIndex) const;
    render::VertexFormat attributeFormat(core::str_view const name) const;
    core::vector<core::pair<core::str, core::u32>> unusedAttribs(
        core::vector<core::u32> const& usedAttribs);

    core::s32 uniformIndex(core::str_view const name) const;
    render::VertexFormat uniformFormat(core::u32 const uniformIndex) const;
    render::VertexFormat uniformFormat(core::str_view const name) const;

private:
    void init(core::u32 const program);
    friend class Shader;

    struct ShaderMetadataPrivate;
    core::PImplPointer<ShaderMetadataPrivate> m_p;
};
}  // namespace haf::res

#endif
