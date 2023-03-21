HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_SHADER_MANAGER_INCLUDE_HPP
#define HAF_RESOURCES_SHADER_MANAGER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/resources/shader.hpp>
#include <haf/include/resources/shader_code.hpp>

namespace haf::res
{
class ShaderManager final
{
public:
    static constexpr char StaticTypeName[] = "ShaderManager";

    explicit ShaderManager() noexcept;
    ~ShaderManager() noexcept;

    void addShader(core::str_view rid, core::sptr<Shader> shader);

    core::size_type setUniformForAll(core::str_view uniformName,
                                     math::Matrix4x4 const& matrix);

    bool setUniform(core::sptr<Shader> const& shader,
                    core::str_view uniformName,
                    math::Matrix4x4 const& matrix);

private:
    core::Dictionary<core::sptr<Shader>> m_shaders;
};

}  // namespace haf::res

#endif
