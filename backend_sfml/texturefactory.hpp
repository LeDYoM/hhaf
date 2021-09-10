#ifndef HAF_BACKEND_SFML_TEXTUREFACTORY_HPP
#define HAF_BACKEND_SFML_TEXTUREFACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <backend_dev/include/iresourcefactories.hpp>
#include "texture.hpp"

namespace haf::backend::sfmlb
{
class Texture;
class TextureFactory : public ITextureFactory
{
public:
    ITexture* loadFromFile(const htps::str& file) override;
    ITexture* loadFromRawMemory(htps::RawMemory* raw_memory) override;
    ~TextureFactory() override;

private:
    htps::vector<htps::sptr<Texture>> texture_cache_;
};
}  // namespace haf::backend::sfmlb

#endif
