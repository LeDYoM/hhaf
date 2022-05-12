#include <htypes/include/types.hpp>

#include "sfml_texture_factory.hpp"
#include "sfml_texture.hpp"
#include <SFML/Graphics/Texture.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
ITexture* SFMLTextureFactory::loadFromRawMemory(RawMemory* raw_memory)
{
    uptr<sf::Texture> texture(muptr<sf::Texture>());
    texture->loadFromMemory(raw_memory->data(), raw_memory->size());
    uptr<SFMLTexture> t{muptr<SFMLTexture>(texture.release(), true)};
    texture_cache_.push_back(htps::move(t));
    return (*(texture_cache_.end() - 1)).get();
}

SFMLTextureFactory::~SFMLTextureFactory() = default;
}  // namespace haf::backend::sfmlb
