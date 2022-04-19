#include <htypes/include/types.hpp>

#include "texturefactory.hpp"
#include <SFML/Graphics/Texture.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
ITexture* TextureFactory::loadFromRawMemory(RawMemory* raw_memory)
{
    uptr<sf::Texture> texture(muptr<sf::Texture>());
    texture->loadFromMemory(raw_memory->data(), raw_memory->size());
    uptr<Texture> t{muptr<Texture>(texture.release(), true)};
    texture_cache_.push_back(std::move(t));
    return (*(texture_cache_.end() - 1)).get();
}

TextureFactory::~TextureFactory() = default;
}  // namespace haf::backend::sfmlb
