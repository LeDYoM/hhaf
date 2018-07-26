#include "shader.hpp"

#include <lib/include/backend/ishader.hpp>
#include <lib/include/backend/ishaderfactory.hpp>

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

    bool Shader::loadFromFile(const str & filename)
    {
        m_private->m_shader = ttfontFactory().loadFromFile(filename);
        return m_private->m_shader != nullptr;
    }
}
