#include <haf/resources/i_include/bmpfont.hpp>
#include "bmpfont_private.hpp"
#include <hlog/include/hlog.hpp>

#include <fstream>

using namespace mtps;

namespace haf::scene
{

BMPFont::BMPFont(const str& file_name)
{
    fontPrivate = new BMFontPrivate;
    fontPrivate->chars_.resize(256U);

    str fontfile(file_name + ".fnt");
    str texturefile(file_name + ".png");
    DisplayLog::info("Starting to Parse Font ", fontfile);
    ParseFont(fontfile);
    DisplayLog::info("Finished Parsing Font ", fontfile);
    DisplayLog::info("Calculating some metrics");
    fontPrivate->adv = 1.0f / (f32)size().x;

    for (u32 i{0U}; i < fontPrivate->chars_.size(); ++i)
    {
        fontPrivate->chars_[i].offsetedPosition = Rectf32(
            static_cast<vector2df>(fontPrivate->chars_[i].offset),
            static_cast<vector2df>(fontPrivate->chars_[i].position.size()));
    }
    DisplayLog::info("Finished Parsing Font ", fontfile);
    DisplayLog::info("Loading pages. Number of pages: ",
                     fontPrivate->pagesData_.size());
    /*
        for (u32 i = 0; i < fontPrivate->pagesData_.size(); ++i)
        {
            fontPrivate->pagesData_[i].it = resource_handler.loadTexture(
                fontPrivate->pagesData_[i].file,
                fontPrivate->pagesData_[i].file);
        }
        DisplayLog::info("Page(s) loaded");
        */
}

vector<str> BMPFont::textureFileNames() const
{
    vector<str> texture_file_names(fontPrivate->pagesData_.size());
    for (const auto& page_data : fontPrivate->pagesData_)
    {
        texture_file_names.push_back(page_data.file);
    }

    return texture_file_names;
}

void BMPFont::setTexturePages(const vector<sptr<ITexture>>& texture_pages)
{
    LogAsserter::log_assert(texture_pages.size() <= fontPrivate->pagesData_.size(),
               "The number of textures to add should be lower or equal that "
               "the number of pages.");

    size_type count{0U};

    for (sptr<ITexture> texture : texture_pages)
    {
        fontPrivate->pagesData_[count].it = texture;
    }
}

BMPFont::~BMPFont()
{
    delete fontPrivate;
}

void filterStr(std::stringstream& line_stream, std::string& value)
{
    bool doNext = true;
    do
    {
        int first_ = value.find_first_of('\"');
        int last_  = value.find_last_of('\"');
        doNext     = (first_ > -1 && first_ == last_);
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
    return fontPrivate->size_;
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
                    converter >> fontPrivate->lineHeight;
                }
                else if (key == "base")
                {
                    converter >> fontPrivate->base;
                }
                else if (key == "scaleW")
                {
                    converter >> fontPrivate->size_.x;
                }
                else if (key == "scaleH")
                {
                    converter >> fontPrivate->size_.y;
                }
                else if (key == "pages")
                {
                    converter >> fontPrivate->pages;
                }
                else if (key == "outline")
                {
                    converter >> fontPrivate->outline;
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
                    fontPrivate->pagesData_.resize(id + 1);
                }
                else if (key == "file")
                {
                    fontPrivate->pagesData_[id].file =
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
                    fontPrivate->fInfo.face = getStr(value).c_str();
                }
                else if (key == "size")
                {
                    converter >> fontPrivate->fInfo.size;
                }
                else if (key == "bold")
                {
                    converter >> fontPrivate->fInfo.bold;
                }
                else if (key == "italic")
                {
                    converter >> fontPrivate->fInfo.italic;
                }
                else if (key == "charset")
                {
                    fontPrivate->fInfo.charset = getStr(value).c_str();
                }
                else if (key == "unicode")
                {
                    converter >> fontPrivate->fInfo.unicode;
                }
                else if (key == "stretchH")
                {
                    converter >> fontPrivate->fInfo.stretchH;
                }
                else if (key == "smooth")
                {
                    converter >> fontPrivate->fInfo.smooth;
                }
                else if (key == "aa")
                {
                    converter >> fontPrivate->fInfo.aa;
                }
                else if (key == "padding")
                {
                    std::string temp;
                    std::getline(converter, temp, ',');
                    fontPrivate->fInfo.padding.left =
                        static_cast<s16>(std::atoi(temp.c_str()));
                    std::getline(converter, temp, ',');
                    fontPrivate->fInfo.padding.top =
                        static_cast<s16>(std::atoi(temp.c_str()));
                    std::getline(converter, temp, ',');
                    fontPrivate->fInfo.padding.setRight(
                        static_cast<s16>(std::atoi(temp.c_str())));
                    std::getline(converter, temp, ',');
                    fontPrivate->fInfo.padding.setBottom(
                        static_cast<s16>(std::atoi(temp.c_str())));
                }
                else if (key == "spacing")
                {
                    std::string temp;
                    std::getline(converter, temp, ',');
                    fontPrivate->fInfo.spacing.x =
                        static_cast<s16>(std::atoi(temp.c_str()));
                    std::getline(converter, temp, ',');
                    fontPrivate->fInfo.spacing.y =
                        static_cast<s16>(std::atoi(temp.c_str()));
                }
                else if (key == "outline")
                {
                    converter >> fontPrivate->fInfo.outline;
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
                fontPrivate->chars_[char_id] = C;
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
            fontPrivate->chars_[first].kearn.emplace_back(second, amount);
        }
    }

    return true;
}

Rectf32 BMPFont::getBounds(const u32 codePoint) const
{
    return fontPrivate->chars_[codePoint].offsetedPosition;
}

Rectf32 BMPFont::getTextureBounds(const u32 codePoint) const
{
    return static_cast<Rectf32>(fontPrivate->chars_[codePoint].position);
}

f32 BMPFont::getAdvance(const u32 codePoint) const
{
    return static_cast<f32>(fontPrivate->chars_[codePoint].xadvance);
}

f32 BMPFont::getLineSpacing() const
{
    return 0.F;
}

f32 BMPFont::getKerning(const u32 first, const u32 second) const
{
    return static_cast<f32>(fontPrivate->chars_[first].GetKerningPair(second));
}

sptr<ITexture> BMPFont::getTexture() const
{
    return fontPrivate->pagesData_[0U].it;
}

vector2df BMPFont::textSize(const str& text) const
{
    return vector2df{};
}
}  // namespace haf::scene
