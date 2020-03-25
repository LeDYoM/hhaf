#include <lib/resources/i_include/bmpfontfactory.hpp>
#include <lib/resources/i_include/bmpfont.hpp>
#include <lib/resources/i_include/texture.hpp>

namespace lib::scene
{
    mtps::sptr<BMPFont> BMPFontFactory::loadFromFile(const mtps::str & file)
    {
        mtps::sptr<scene::BMPFont> font(mtps::msptr<scene::BMPFont>(file));
        return font;
    }

    mtps::sptr<BMPFont> BMPFontFactory::loadFromRawMemory(mtps::RawMemory *)
    {
        mtps::sptr<scene::BMPFont> font(mtps::msptr<scene::BMPFont>(""));
        return font;
/*
        mtps::uptr<sf::Font> font(mtps::muptr<sf::Font>());
        RawMemory internal_raw_memory(*raw_memory);
        font->loadFromMemory(internal_raw_memory.data(), internal_raw_memory.size());
        mtps::uptr<TTFont> t{ mtps::muptr<TTFont>(std::move(font), std::move(internal_raw_memory)) };
        m_fontCache.push_back(std::move(t));
        return (*(m_fontCache.end() - 1)).get();
        */
    }
}
