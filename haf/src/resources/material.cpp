#include <haf/include/resources/material.hpp>

using namespace haf::core;

namespace haf::res
{
Material::Material(core::sptr<Shader> shader) : m_shader{core::move(shader)}
{}

Material::~Material() = default;

}  // namespace haf::res