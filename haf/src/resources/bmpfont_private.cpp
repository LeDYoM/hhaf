#include <htypes/include/types.hpp>
#include "resources/bmpfont_private.hpp"
#include "resources/bmpfont.hpp"

#include <string>
#include <fstream>

using namespace htps;

namespace haf::res
{
s16 my_stoi(std::string const& data)
{
    try
    {
        return static_cast<s16>(std::stoi(data));
    }
    catch (...)
    {}
    return 0;
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

s32 CharDescriptor::GetKerningPair(const htps::u32 second) const
{
    const auto iterator(kearn.cfind_if([second](const auto& this_kearn) {
        return this_kearn.second == second;
    }));

    return iterator == kearn.cend() ? 0 : iterator->amount;
}

bool BMPFont::BMFontPrivate::ParseFont(const str& fontfile)
{
    std::ifstream font_file_stream{fontfile.c_str()};
    std::size_t i{0U};
    u32 first{0U};
    u32 second{0U};
    s32 amount{0};

    CharDescriptor charDescriptor;

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
                    converter >> lineHeight;
                }
                else if (key == "base")
                {
                    converter >> base;
                }
                else if (key == "scaleW")
                {
                    converter >> size_.x;
                }
                else if (key == "scaleH")
                {
                    converter >> size_.y;
                }
                else if (key == "pages")
                {
                    converter >> pages;
                }
                else if (key == "outline")
                {
                    converter >> outline;
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
                    pagesData_.resize(id + 1);
                }
                else if (key == "file")
                {
                    pagesData_[id].file = str(getStr(value).c_str());
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
                    fInfo.face = getStr(value).c_str();
                }
                else if (key == "size")
                {
                    converter >> fInfo.size;
                }
                else if (key == "bold")
                {
                    converter >> fInfo.bold;
                }
                else if (key == "italic")
                {
                    converter >> fInfo.italic;
                }
                else if (key == "charset")
                {
                    fInfo.charset = getStr(value).c_str();
                }
                else if (key == "unicode")
                {
                    converter >> fInfo.unicode;
                }
                else if (key == "stretchH")
                {
                    converter >> fInfo.stretchH;
                }
                else if (key == "smooth")
                {
                    converter >> fInfo.smooth;
                }
                else if (key == "aa")
                {
                    converter >> fInfo.aa;
                }
                else if (key == "padding")
                {
                    std::string temp;
                    std::getline(converter, temp, ',');
                    fInfo.padding.left = my_stoi(temp);
                    std::getline(converter, temp, ',');
                    fInfo.padding.top = my_stoi(temp);
                    std::getline(converter, temp, ',');
                    fInfo.padding.setRight(my_stoi(temp));
                    std::getline(converter, temp, ',');
                    fInfo.padding.setBottom(my_stoi(temp));
                }
                else if (key == "spacing")
                {
                    std::string temp;
                    std::getline(converter, temp, ',');
                    fInfo.spacing.x = my_stoi(temp);
                    std::getline(converter, temp, ',');
                    fInfo.spacing.y = my_stoi(temp);
                }
                else if (key == "outline")
                {
                    converter >> fInfo.outline;
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
                    converter >> charDescriptor.position.left;
                }
                else if (key == "y")
                {
                    converter >> charDescriptor.position.top;
                }
                else if (key == "width")
                {
                    u16 temp;
                    converter >> temp;
                    charDescriptor.position.width = temp;
                }
                else if (key == "height")
                {
                    u16 temp;
                    converter >> temp;
                    charDescriptor.position.height = temp;
                }
                else if (key == "xoffset")
                {
                    converter >> charDescriptor.offset.x;
                }
                else if (key == "yoffset")
                {
                    converter >> charDescriptor.offset.y;
                }
                else if (key == "xadvance")
                {
                    converter >> charDescriptor.xadvance;
                }
                else if (key == "page")
                {
                    converter >> charDescriptor.page;
                }
            }

            if (char_id < 256)
            {
                chars_[char_id] = charDescriptor;
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
            chars_[first].kearn.emplace_back(second, amount);
        }
    }

    return true;
}
}  // namespace haf::res
