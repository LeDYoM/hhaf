#include "shader.hpp"

#include <backend_dev/include/ishader.hpp>
#include <map>

namespace lib::scene
{
    struct Shader::ShaderPrivate
    {
        backend::IShader *m_shader;
    };

    Shader::Shader(backend::IShader* shader) :
        m_private{ new ShaderPrivate{ std::move(shader) } } {}

    Shader::~Shader() = default;
}
