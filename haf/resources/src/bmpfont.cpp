#include <resources/i_include/bmpfont.hpp>
#include <resources/i_include/bmpfont_private.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::res
{

BMPFont::BMPFont(const str& file_name)
{
    p_ = new BMFontPrivate;
    p_->chars_.resize(256U);

    str fontfile(file_name);
    DisplayLog::info("Starting to Parse Font ", fontfile);
    p_->ParseFont(fontfile);
    DisplayLog::info("Finished Parsing Font ", fontfile);
    DisplayLog::info("Calculating some metrics");
    p_->adv = 1.0f / (f32)size().x;

    for (u32 i{0U}; i < p_->chars_.size(); ++i)
    {
        p_->chars_[i].offsetedPosition = Rectf32(
            static_cast<vector2df>(p_->chars_[i].offset),
            static_cast<vector2df>(p_->chars_[i].position.size()));
    }
    DisplayLog::info("Finished Parsing Font ", fontfile);
    DisplayLog::info("Loading pages. Number of pages: ",
                     p_->pagesData_.size());
}

vector<str> BMPFont::textureFileNames() const
{
    vector<str> texture_file_names(p_->pagesData_.size());
    for (const auto& page_data : p_->pagesData_)
    {
        texture_file_names.push_back(page_data.file);
    }

    return texture_file_names;
}

void BMPFont::setTexturePages(const vector<sptr<ITexture>>& texture_pages)
{
    LogAsserter::log_assert(
        texture_pages.size() <= p_->pagesData_.size(),
        "The number of textures to add should be lower or equal that "
        "the number of pages.");

    size_type count{0U};

    for (sptr<ITexture> texture : texture_pages)
    {
        p_->pagesData_[count].it = texture;
    }
}

BMPFont::~BMPFont()
{
    delete p_;
}

const vector2du32& BMPFont::size() const
{
    return p_->size_;
}

Rectf32 BMPFont::getBounds(const u32 codePoint) const
{
    return p_->chars_[codePoint].offsetedPosition;
}

Rectf32 BMPFont::getTextureBounds(const u32 codePoint) const
{
    return static_cast<Rectf32>(p_->chars_[codePoint].position);
}

f32 BMPFont::getAdvance(const u32 codePoint) const
{
    return static_cast<f32>(p_->chars_[codePoint].xadvance);
}

f32 BMPFont::getLineSpacing() const
{
    return 0.F;
}

f32 BMPFont::getKerning(const u32 first, const u32 second) const
{
    return static_cast<f32>(p_->chars_[first].GetKerningPair(second));
}

sptr<ITexture> BMPFont::getTexture() const
{
    return p_->pagesData_[0U].it;
}

}  // namespace haf::res
