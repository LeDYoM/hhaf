#include "ttfontinstance.hpp"
#include "ttfont.hpp"

#include <backend_dev/include/ittfont.hpp>

namespace lib::scene
{
    using namespace backend;

	TTFontInstance::TTFontInstance(const TTFont &parent, const u32 characterSize)
        : m_parentInstance{parent}, m_characterSize{characterSize}
    {
    }

	TTFontInstance::~TTFontInstance() = default;

	Rectf32 TTFontInstance::getBounds(const u32 codePoint) const
	{
		return m_parentInstance.getBounds(codePoint, m_characterSize);
	}

	Rectf32 TTFontInstance::getTextureBounds(const u32 codePoint) const
	{
		return m_parentInstance.getTextureBounds(codePoint, m_characterSize);
	}

	f32 TTFontInstance::getAdvance(const u32 codePoint) const
	{
		return m_parentInstance.getAdvance(codePoint, m_characterSize);
	}

	f32 TTFontInstance::getLineSpacing() const
    {
        return m_parentInstance.getLineSpacing(m_characterSize);
    }

    f32 TTFontInstance::getKerning(const u32 first, const u32 second) const
    {
        return m_parentInstance.getKerning(first, second, m_characterSize);
    }

    sptr<ITexture> TTFontInstance::getTexture() const
    {
        return std::dynamic_pointer_cast<ITexture>(m_parentInstance.getTexture(m_characterSize));
    }

    vector2df TTFontInstance::textSize(const str&text) const
    {
        return m_parentInstance.textSize(text, m_characterSize);
    }
}
