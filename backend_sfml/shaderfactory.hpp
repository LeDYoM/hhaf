#ifndef HAF_BACKEND_SFML_SHADERFACTORY_HPP
#define HAF_BACKEND_SFML_SHADERFACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <backend_dev/include/iresourcefactories.hpp>
#include "shader.hpp"

namespace haf::backend::sfmlb
{
class ShaderFactory : public IShaderFactory
{
public:
    virtual IShader* loadFromFile(const htps::str& file) override;
    ~ShaderFactory() override;

private:
    htps::vector<htps::sptr<Shader>> m_shaderCache;
};
}  // namespace haf::backend::sfmlb

#endif
