HAF_PRAGMA_ONCE
#ifndef HAF_RESOURCES_SHADER_INCLUDE_HPP
#define HAF_RESOURCES_SHADER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/resources/shader_code.hpp>
#include <haf/include/resources/iresource.hpp>
#include <haf/include/resources/vertex_buffer_object.hpp>
#include <haf/include/core/matrix4x4.hpp>

namespace haf::res
{
class Shader final : public IResource
{
public:
    static constexpr ResourceType const StaticResourceType{
        ResourceType::Shader};

    Shader(core::sptr<VertexShaderCode> vsc,
           core::sptr<TessellationControlShaderCode> tcsc,
           core::sptr<TessellationEvaluationShaderCode> tesc,
           core::sptr<GeometryShaderCode> gsc,
           core::sptr<FragmentShaderCode> fsc,
           core::sptr<ComputeShaderCode> csc);

    ~Shader() override;

    friend struct ShaderVaoHelper;

    constexpr ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }

    static constexpr auto staticTypeName()
    {
        return resourceTypeName(StaticResourceType);
    }

    void setVertexAttribFormatForVao(core::u32 const vao,
                                     core::u32 const attrib_index);

    core::u32 numAttribs() const;
    render::VertexFormat vertexFormat(core::u32 const index) const;

    void bind();
    void unbind();

    bool isValid() const override;
    core::u32 handle() const;

    void setUniform(core::str_view const name, math::Matrix4x4 const& m4x4);
    void setUniform(core::s32 const index, math::Matrix4x4 const& m4x4);

    core::s32 attributeIndex(core::str_view const name) const;
    render::VertexFormat attributeFormat(core::u32 const attributeIndex) const;
    render::VertexFormat attributeFormat(core::str_view const name) const;
    core::vector<core::pair<core::str, core::u32>> unusedAttribs(
        core::vector<core::u32> const& usedAttribs);

    core::s32 uniformIndex(core::str_view const name) const;
    render::VertexFormat uniformFormat(core::u32 const uniformIndex) const;
    render::VertexFormat uniformFormat(core::str_view const name) const;

private:
    struct ShaderPrivate;
    core::PImplPointer<ShaderPrivate> m_p;
};
}  // namespace haf::res

#endif
