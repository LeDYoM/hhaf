#include "bmpfontfactory.hpp"
#include "bmpfont.hpp"
#include "texture.hpp"

namespace lib::scene
{
    sptr<BMPFont> BMPFontFactory::loadFromFile(const str & file)
    {
        sptr<scene::BMPFont> font(msptr<scene::BMPFont>(file, file));
//        font->loadFromFile(file.c_str());
//        uptr<TTFont> t{ muptr<TTFont>(std::move(font), RawMemory{} ) };
        m_fontCache.push_back(font);
        return font;
    }

    sptr<BMPFont> BMPFontFactory::loadFromRawMemory(RawMemory *)
    {
        sptr<scene::BMPFont> font(msptr<scene::BMPFont>("",""));
//        font->loadFromFile(file.c_str());
//        uptr<TTFont> t{ muptr<TTFont>(std::move(font), RawMemory{} ) };
        m_fontCache.push_back(font);
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

    BMPFontFactory::~BMPFontFactory()
    {
        m_fontCache.clear();
        m_fontCache.shrink_to_fit();
    }
}
