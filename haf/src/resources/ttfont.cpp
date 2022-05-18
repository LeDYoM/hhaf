#include "ttfont.hpp"
#include "ttfontinstance.hpp"

#include <backend_dev/include/ittfont.hpp>

#include <map>
#include <algorithm>

using namespace htps;

namespace haf::res
{
struct TTFont::FontPrivate
{
    FontPrivate(backend::ITTFont* font) : font_{font} {}
    backend::ITTFont* font_;
    std::map<u32, sptr<TTFontInstance>> font_map_;
};

TTFont::TTFont(backend::ITTFont* const font) : priv_{muptr<FontPrivate>(font)}
{}

TTFont::~TTFont() = default;

Rectf32 TTFont::getBounds(const u32 codePoint, const u32 characterSize) const
{
    return priv_->font_->getBounds(codePoint, characterSize);
}

Rectf32 TTFont::getTextureBounds(const u32 codePoint,
                                 const u32 characterSize) const
{
    return priv_->font_->getTextureBounds(codePoint, characterSize);
}

f32 TTFont::getAdvance(const u32 codePoint, const u32 characterSize) const
{
    return priv_->font_->getAdvance(codePoint, characterSize);
}

f32 TTFont::getLineSpacing(const u32 characterSize) const
{
    return priv_->font_->getLineSpacing(characterSize);
}

f32 TTFont::getKerning(const u32 first,
                       const u32 second,
                       const u32 characterSize) const
{
    return priv_->font_->getKerning(first, second, characterSize);
}

str TTFont::getTexture(const u32 characterSize, char const character) const
{
    return (priv_->font_ != nullptr)
        ? priv_->font_->getTexture(characterSize, character)
        : "";
}

sptr<IFont> TTFont::font(const u32 charactersize)
{
    if (auto iterator = priv_->font_map_.find(charactersize);
        iterator == priv_->font_map_.end())
    {
        sptr<TTFontInstance> newFont{
            msptr<TTFontInstance>(*this, charactersize)};
        return priv_->font_map_[charactersize] = newFont;
    }
    else
    {
        return (*iterator).second;
    }
}
}  // namespace haf::res
