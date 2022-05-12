#ifndef HAF_BACKEND_SFML_TEXTUREFACTORY_HPP
#define HAF_BACKEND_SFML_TEXTUREFACTORY_HPP

#include <htypes/include/rawmemory.hpp>

#include <backend_dev/include/iresourcefactories.hpp>

namespace haf::backend::sfmlb
{
class SFMLTexture;
class SFMLTextureFactory : public ITextureFactory
{
public:
    ITexture* loadFromRawMemory(htps::RawMemory* raw_memory) override;
    ~SFMLTextureFactory() override;

private:
    htps::vector<htps::sptr<SFMLTexture>> texture_cache_;
};
}  // namespace haf::backend::sfmlb

#endif
