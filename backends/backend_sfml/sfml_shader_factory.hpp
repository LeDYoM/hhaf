#ifndef HAF_BACKEND_SFML_SHADERFACTORY_HPP
#define HAF_BACKEND_SFML_SHADERFACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/resource_load_parameters.hpp>

namespace haf::backend::sfmlb
{
class SFMLShader;
class SFMLShaderFactory : public IShaderFactory
{
public:
    IShader* loadFromRawMemory(
        ResourceLoadParameters const& resource_load_parameters) override;

    ~SFMLShaderFactory() override;

private:
    htps::vector<htps::sptr<SFMLShader>> shader_cache_;
};
}  // namespace haf::backend::sfmlb

#endif
