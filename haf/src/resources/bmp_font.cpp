#include "bmp_font.hpp"

#include <hlog/include/hlog.hpp>
#include <backend_dev/include/ifont.hpp>
#include "texture.hpp"

using namespace htps;

namespace haf::res
{
BMPFont::BMPFont(backend::IBMPFont* font) : ifont_{font}
{}

BMPFont::~BMPFont() = default;

Rectf32 BMPFont::getBounds(const u32 codePoint) const
{
    return ifont_->getBounds(codePoint);
}

Rectf32 BMPFont::getTextureBounds(const u32 codePoint) const
{
    return ifont_->getTextureBounds(codePoint);
}

f32 BMPFont::getAdvance(u32 const codePoint) const
{
    return ifont_->getAdvance(codePoint);
}

f32 BMPFont::getLineSpacing() const
{
    return ifont_->getLineSpacing();
}

f32 BMPFont::getKerning(u32 const first, u32 const second) const
{
    return ifont_->getKerning(first, second);
}

sptr<ITexture> BMPFont::getTexture(char const character)
{
    return std::dynamic_pointer_cast<ITexture>(
        msptr<Texture>(ifont_->getTexture(character)));
}

vector<pair<str,str>> BMPFont::texturesToLoad() const
{
    return ifont_->texturesToLoad();
}

void BMPFont::setTexturePages(
    vector<backend::ITexture const*> const& texture_pages)
{
    ifont_->setTexturePages(texture_pages);
}

}  // namespace haf::res
