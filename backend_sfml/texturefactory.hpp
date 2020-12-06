#ifndef HAF_BACKEND_SFML_TEXTUREFACTORY_HPP
#define HAF_BACKEND_SFML_TEXTUREFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <backend_dev/include/iresourcefactories.hpp>
#include "texture.hpp"

namespace haf::backend::sfmlb
{
    class Texture;
    class TextureFactory : public ITextureFactory
    {
    public:
        ITexture *loadFromFile(const mtps::str &file) override;
        ITexture *loadFromRawMemory(mtps::RawMemory *raw_memory) override;
        ~TextureFactory() override;
    private:
        mtps::vector<mtps::sptr<Texture>> m_textureCache;
    };
}

#endif
