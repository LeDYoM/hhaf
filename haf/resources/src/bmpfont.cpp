#include <resources/i_include/bmpfont.hpp>
#include <resources/i_include/bmpfont_private.hpp>
#include <hlog/include/hlog.hpp>

#include <fstream>

using namespace htps;

namespace haf::res
{

BMPFont::BMPFont(const str& file_name)
{
    fontPrivate_ = new BMFontPrivate;
    fontPrivate_->chars_.resize(256U);

    str fontfile(file_name);
    DisplayLog::info("Starting to Parse Font ", fontfile);
    ParseFont(fontfile);
    DisplayLog::info("Finished Parsing Font ", fontfile);
    DisplayLog::info("Calculating some metrics");
    fontPrivate_->adv = 1.0f / (f32)size().x;

    for (u32 i{0U}; i < fontPrivate_->chars_.size(); ++i)
    {
        fontPrivate_->chars_[i].offsetedPosition = Rectf32(
            static_cast<vector2df>(fontPrivate_->chars_[i].offset),
            static_cast<vector2df>(fontPrivate_->chars_[i].position.size()));
    }
    DisplayLog::info("Finished Parsing Font ", fontfile);
    DisplayLog::info("Loading pages. Number of pages: ",
                     fontPrivate_->pagesData_.size());
}

vector<str> BMPFont::textureFileNames() const
{
    vector<str> texture_file_names(fontPrivate_->pagesData_.size());
    for (const auto& page_data : fontPrivate_->pagesData_)
    {
        texture_file_names.push_back(page_data.file);
    }

    return texture_file_names;
}

void BMPFont::setTexturePages(const vector<sptr<ITexture>>& texture_pages)
{
    LogAsserter::log_assert(
        texture_pages.size() <= fontPrivate_->pagesData_.size(),
        "The number of textures to add should be lower or equal that "
        "the number of pages.");

    size_type count{0U};

    for (sptr<ITexture> texture : texture_pages)
    {
        fontPrivate_->pagesData_[count].it = texture;
    }
}

BMPFont::~BMPFont()
{
    delete fontPrivate_;
}

void filterStr(std::stringstream& line_stream, std::string& value)
{
    bool doNext = true;
    do
    {
        auto const first_ = value.find_first_of('\"');
        auto const last_  = value.find_last_of('\"');
        doNext            = (static_cast<s32>(first_) > -1 && first_ == last_);
        if (doNext)
        {
            std::string readTemp;
            line_stream >> readTemp;
            value += " " + readTemp;
        }
    } while (doNext);
}

const vector2du32& BMPFont::size() const
{
    return fontPrivate_->size_;
}

std::string getStr(const std::string& read)
{
    std::string result;

    for (char ch : read)
    {
        if (ch != '"')
        {
            result.push_back(ch);
        }
    }
    return result;
}

bool BMPFont::ParseFont(const str& fontfile)
{
    std::ifstream font_file_stream(fontfile.c_str());
    std::size_t i{0U};
    u32 first{0U};
    u32 second{0U};
    s32 amount{0};

    CharDescriptor C;

    while (font_file_stream && !font_file_stream.eof())
    {
        std::string line;
        std::string read;
        std::string key;
        std::string value;

        std::stringstream line_stream;
        std::getline(font_file_stream, line);
        line_stream << line;

        // read the line's type
        line_stream >> read;
        if (read == "common")
        {
            // this holds common data
            while (!line_stream.eof())
            {
                std::stringstream converter;
                line_stream >> read;
                i     = read.find('=');
                key   = read.substr(0, i);
                value = read.substr(i + 1).c_str();

                // assign the correct value
                converter << value;
                if (key == "lineHeight")
                {
                    converter >> fontPrivate_->lineHeight;
                }
                else if (key == "base")
                {
                    converter >> fontPrivate_->base;
                }
                else if (key == "scaleW")
                {
                    converter >> fontPrivate_->size_.x;
                }
                else if (key == "scaleH")
                {
                    converter >> fontPrivate_->size_.y;
                }
                else if (key == "pages")
                {
                    converter >> fontPrivate_->pages;
                }
                else if (key == "outline")
                {
                    converter >> fontPrivate_->outline;
                }
            }
        }
        else if (read == "page")
        {
            // this holds common data
            while (!line_stream.eof())
            {
                std::stringstream converter;
                line_stream >> read;
                i     = read.find('=');
                key   = read.substr(0, i);
                value = read.substr(i + 1);
                u32 id{0U};

                filterStr(line_stream, value);

                // assign the correct value
                converter << value;
                if (key == "id")
                {
                    converter >> id;
                    fontPrivate_->pagesData_.resize(id + 1);
                }
                else if (key == "file")
                {
                    fontPrivate_->pagesData_[id].file =
                        str(getStr(value).c_str());
                }
            }
        }
        else if (read == "info")
        {
            // this holds info font data
            while (!line_stream.eof())
            {
                std::stringstream converter;
                line_stream >> read;
                i     = read.find('=');
                key   = read.substr(0, i);
                value = read.substr(i + 1);

                filterStr(line_stream, value);
                converter << value;
                if (key == "face")
                {
                    fontPrivate_->fInfo.face = getStr(value).c_str();
                }
                else if (key == "size")
                {
                    converter >> fontPrivate_->fInfo.size;
                }
                else if (key == "bold")
                {
                    converter >> fontPrivate_->fInfo.bold;
                }
                else if (key == "italic")
                {
                    converter >> fontPrivate_->fInfo.italic;
                }
                else if (key == "charset")
                {
                    fontPrivate_->fInfo.charset = getStr(value).c_str();
                }
                else if (key == "unicode")
                {
                    converter >> fontPrivate_->fInfo.unicode;
                }
                else if (key == "stretchH")
                {
                    converter >> fontPrivate_->fInfo.stretchH;
                }
                else if (key == "smooth")
                {
                    converter >> fontPrivate_->fInfo.smooth;
                }
                else if (key == "aa")
                {
                    converter >> fontPrivate_->fInfo.aa;
                }
                else if (key == "padding")
                {
                    std::string temp;
                    std::getline(converter, temp, ',');
                    fontPrivate_->fInfo.padding.left =
                        static_cast<s16>(std::atoi(temp.c_str()));
                    std::getline(converter, temp, ',');
                    fontPrivate_->fInfo.padding.top =
                        static_cast<s16>(std::atoi(temp.c_str()));
                    std::getline(converter, temp, ',');
                    fontPrivate_->fInfo.padding.setRight(
                        static_cast<s16>(std::atoi(temp.c_str())));
                    std::getline(converter, temp, ',');
                    fontPrivate_->fInfo.padding.setBottom(
                        static_cast<s16>(std::atoi(temp.c_str())));
                }
                else if (key == "spacing")
                {
                    std::string temp;
                    std::getline(converter, temp, ',');
                    fontPrivate_->fInfo.spacing.x =
                        static_cast<s16>(std::atoi(temp.c_str()));
                    std::getline(converter, temp, ',');
                    fontPrivate_->fInfo.spacing.y =
                        static_cast<s16>(std::atoi(temp.c_str()));
                }
                else if (key == "outline")
                {
                    converter >> fontPrivate_->fInfo.outline;
                }
            }
        }
        else if (read == "char")
        {
            // This is data for each specific character.
            int char_id{0};

            while (!line_stream.eof())
            {
                std::stringstream converter;
                line_stream >> read;
                i     = read.find('=');
                key   = read.substr(0, i);
                value = read.substr(i + 1);

                // Assign the correct value
                converter << value;
                if (key == "id")
                {
                    converter >> char_id;
                }
                else if (key == "x")
                {
                    converter >> C.position.left;
                }
                else if (key == "y")
                {
                    converter >> C.position.top;
                }
                else if (key == "width")
                {
                    u16 temp;
                    converter >> temp;
                    C.position.width = temp;
                }
                else if (key == "height")
                {
                    u16 temp;
                    converter >> temp;
                    C.position.height = temp;
                }
                else if (key == "xoffset")
                {
                    converter >> C.offset.x;
                }
                else if (key == "yoffset")
                {
                    converter >> C.offset.y;
                }
                else if (key == "xadvance")
                {
                    converter >> C.xadvance;
                }
                else if (key == "page")
                {
                    converter >> C.page;
                }
            }
            if (char_id < 256)
            {
                fontPrivate_->chars_[char_id] = C;
            }
        }
        else if (read == "kernings")
        {
            while (!line_stream.eof())
            {
                std::stringstream converter;
                line_stream >> read;
                i     = read.find('=');
                key   = read.substr(0, i);
                value = read.substr(i + 1);

                // assign the correct value
                converter << value;
                //      if( key == "count" )
                //          {converter >> KernCount; }
            }
        }

        else if (read == "kerning")
        {
            while (!line_stream.eof())
            {
                std::stringstream converter;
                line_stream >> read;
                i     = read.find('=');
                key   = read.substr(0, i);
                value = read.substr(i + 1);

                converter << value;
                if (key == "first")
                {
                    converter >> first;
                }

                else if (key == "second")
                {
                    converter >> second;
                }

                else if (key == "amount")
                {
                    converter >> amount;
                }
            }
            fontPrivate_->chars_[first].kearn.emplace_back(second, amount);
        }
    }

    return true;
}

Rectf32 BMPFont::getBounds(const u32 codePoint) const
{
    return fontPrivate_->chars_[codePoint].offsetedPosition;
}

Rectf32 BMPFont::getTextureBounds(const u32 codePoint) const
{
    return static_cast<Rectf32>(fontPrivate_->chars_[codePoint].position);
}

f32 BMPFont::getAdvance(const u32 codePoint) const
{
    return static_cast<f32>(fontPrivate_->chars_[codePoint].xadvance);
}

f32 BMPFont::getLineSpacing() const
{
    return 0.F;
}

f32 BMPFont::getKerning(const u32 first, const u32 second) const
{
    return static_cast<f32>(fontPrivate_->chars_[first].GetKerningPair(second));
}

sptr<ITexture> BMPFont::getTexture() const
{
    return fontPrivate_->pagesData_[0U].it;
}

}  // namespace haf::res
