#include "shader.hpp"
#include <backend_dev/include/ishader.hpp>

namespace haf::res
{
Shader::Shader(backend::IShader* shader) : priv_{shader}
{}

Shader::~Shader() = default;

backend::IShader const* Shader::backEndShader() const noexcept
{
    return priv_;
}

}  // namespace haf::res
