#include <lib/resources/i_include/ttfontinstance.hpp>
#include <lib/resources/i_include/ttfont.hpp>

#include <backend_dev/include/ittfont.hpp>

namespace lib::scene
{
    using namespace backend;

    TTFontInstance::TTFontInstance(const TTFont &parent, const mtps::u32 characterSize)
        : m_parentInstance{parent}, m_characterSize{characterSize}
    {
    }

    TTFontInstance::~TTFontInstance() = default;

    mtps::Rectf32 TTFontInstance::getBounds(const mtps::u32 codePoint) const
    {
        return m_parentInstance.getBounds(codePoint, m_characterSize);
    }

    mtps::Rectf32 TTFontInstance::getTextureBounds(const mtps::u32 codePoint) const
    {
        return m_parentInstance.getTextureBounds(codePoint, m_characterSize);
    }

    mtps::f32 TTFontInstance::getAdvance(const mtps::u32 codePoint) const
    {
        return m_parentInstance.getAdvance(codePoint, m_characterSize);
    }

    mtps::f32 TTFontInstance::getLineSpacing() const
    {
        return m_parentInstance.getLineSpacing(m_characterSize);
    }

    mtps::f32 TTFontInstance::getKerning(const mtps::u32 first, const mtps::u32 second) const
    {
        return m_parentInstance.getKerning(first, second, m_characterSize);
    }

    mtps::sptr<ITexture> TTFontInstance::getTexture() const
    {
        return std::dynamic_pointer_cast<ITexture>(m_parentInstance.getTexture(m_characterSize));
    }

    mtps::vector2df TTFontInstance::textSize(const mtps::str &text) const
    {
        return m_parentInstance.textSize(text, m_characterSize);
    }
}
