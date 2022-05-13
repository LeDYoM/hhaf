#include "default_bmp_font.hpp"
#include "default_bmp_font_private.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::res
{
DefaultBMPFont::DefaultBMPFont() : p_{muptr<DefaultBMFontPrivate>()}
{}

void DefaultBMPFont::loadFromMemory(htps::RawMemory* data)
{
    p_->chars_.resize(256U);
    str temp{data->to_str()};
    p_->ParseFont(temp);
    DisplayLog::info("Calculating some metrics");
    p_->adv = 1.0F / static_cast<f32>(size().x);

    for (auto& charDescriptor : p_->chars_)
    {
        charDescriptor.offsetedPosition =
            Rectf32{static_cast<vector2df>(charDescriptor.offset),
                    static_cast<vector2df>(charDescriptor.position.size())};
    }

    //    DisplayLog::info("Finished Parsing Font ", fontfile);
    DisplayLog::info("Loading pages. Number of pages: ", p_->pagesData_.size());
}

vector<pair<str, str>> DefaultBMPFont::texturesToLoad() const
{
    vector<pair<str,str>> textures_to_load(p_->pagesData_.size());
    for (const auto& page_data : p_->pagesData_)
    {
        textures_to_load.emplace_back(page_data.file, page_data.file);
    }

    return textures_to_load;
}

void DefaultBMPFont::setTexturePages(
    const vector<backend::ITexture const*>& texture_pages)
{
    LogAsserter::log_assert(
        texture_pages.size() <= p_->pagesData_.size(),
        "The number of textures to add should be lower or equal that "
        "the number of pages.");

    size_type count{0U};

    for (backend::ITexture const* texture : texture_pages)
    {
        p_->pagesData_[count].texture = texture;
    }
}

DefaultBMPFont::~DefaultBMPFont() = default;

const vector2du32& DefaultBMPFont::size() const
{
    return p_->size_;
}

Rectf32 DefaultBMPFont::getBounds(const u32 codePoint) const
{
    return p_->chars_[codePoint].offsetedPosition;
}

Rectf32 DefaultBMPFont::getTextureBounds(const u32 codePoint) const
{
    return static_cast<Rectf32>(p_->chars_[codePoint].position);
}

f32 DefaultBMPFont::getAdvance(const u32 codePoint) const
{
    return static_cast<f32>(p_->chars_[codePoint].xadvance);
}

f32 DefaultBMPFont::getLineSpacing() const
{
    return 0.F;
}

f32 DefaultBMPFont::getKerning(const u32 first, const u32 second) const
{
    return static_cast<f32>(p_->chars_[first].GetKerningPair(second));
}

backend::ITexture const* DefaultBMPFont::getTexture(char const /*character*/)
{
    return p_->pagesData_[0U].texture;
}

}  // namespace haf::res
