#ifndef HAF_BACKEND_SFML_TEXTUREFACTORY_HPP
#define HAF_BACKEND_SFML_TEXTUREFACTORY_HPP

#include <htypes/include/rawmemory.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/resource_load_parameters.hpp>

namespace haf::backend::sfmlb
{
class SFMLTexture;
class SFMLTextureFactory : public ITextureFactory
{
public:
    ITexture* loadFromRawMemory(
        ResourceLoadParameters const& resource_load_parameters) override;
    ~SFMLTextureFactory() override;

private:
    htps::vector<htps::sptr<SFMLTexture>> texture_cache_;
};
}  // namespace haf::backend::sfmlb

#endif
