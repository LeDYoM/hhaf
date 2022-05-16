#include "ttfontinstance.hpp"
#include "ttfont.hpp"

#include <backend_dev/include/ittfont.hpp>

using namespace htps;

namespace haf::res
{
using namespace backend;

TTFontInstance::TTFontInstance(const TTFont& parent, const u32 characterSize) :
    parent_instance_{parent}, character_size_{characterSize}
{}

TTFontInstance::~TTFontInstance() = default;

Rectf32 TTFontInstance::getBounds(const u32 codePoint) const
{
    return parent_instance_.getBounds(codePoint, character_size_);
}

Rectf32 TTFontInstance::getTextureBounds(const u32 codePoint) const
{
    return parent_instance_.getTextureBounds(codePoint, character_size_);
}

f32 TTFontInstance::getAdvance(const u32 codePoint) const
{
    return parent_instance_.getAdvance(codePoint, character_size_);
}

f32 TTFontInstance::getLineSpacing() const
{
    return parent_instance_.getLineSpacing(character_size_);
}

f32 TTFontInstance::getKerning(const u32 first, const u32 second) const
{
    return parent_instance_.getKerning(first, second, character_size_);
}

str TTFontInstance::getTexture(char const character)
{
    return parent_instance_.getTexture(character_size_, character);
}

}  // namespace haf::res
