#include "shader.hpp"
#include <backend_dev/include/ishader.hpp>
#include "render/render_data_conversion.hpp"

namespace haf::res
{
Shader::Shader(backend::IShader* shader) : priv_{shader}
{}

Shader::~Shader() = default;

void Shader::setUniform(htps::str const& name, ITexture* value)
{
    priv_->setUniform(name, render::to_backend(value));
}

void Shader::setUniform(htps::str const& name, bool const& value)
{
    priv_->setUniform(name, value);
}

void Shader::setUniform(htps::str const& name, htps::vector2df const& value)
{
    priv_->setUniform(name, value);
}

backend::IShader const* Shader::backEndShader() const noexcept
{
    return priv_;
}

}  // namespace haf::res
