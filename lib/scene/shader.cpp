#include "shader.hpp"

#include <lib/include/backend/ishader.hpp>
#include <lib/core/backendfactory.hpp>

#include <map>

namespace lib::scene
{
    using namespace backend;

    struct Shader::ShaderPrivate
    {
        IShader *m_shader;
    };

    Shader::Shader(backend::IShader* shader) :
        m_private{ new ShaderPrivate{ std::move(shader) } } {}

    Shader::~Shader() = default;
}
