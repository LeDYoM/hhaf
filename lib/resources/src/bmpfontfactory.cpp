#include <lib/resources/i_include/bmpfontfactory.hpp>
#include <lib/resources/i_include/bmpfont.hpp>
#include <lib/resources/i_include/texture.hpp>

namespace lib::scene
{
    sptr<BMPFont> BMPFontFactory::loadFromFile(const str & file)
    {
        sptr<scene::BMPFont> font(msptr<scene::BMPFont>(file));
        return font;
    }

    sptr<BMPFont> BMPFontFactory::loadFromRawMemory(RawMemory *)
    {
        sptr<scene::BMPFont> font(msptr<scene::BMPFont>(""));
        return font;
/*
        uptr<sf::Font> font(muptr<sf::Font>());
        RawMemory internal_raw_memory(*raw_memory);
        font->loadFromMemory(internal_raw_memory.data(), internal_raw_memory.size());
        uptr<TTFont> t{ muptr<TTFont>(std::move(font), std::move(internal_raw_memory)) };
        m_fontCache.push_back(std::move(t));
        return (*(m_fontCache.end() - 1)).get();
        */
    }
}
