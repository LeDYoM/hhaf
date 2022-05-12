#include <haf/include/scene_nodes/text_base_size.hpp>

using namespace htps;

namespace haf::scene::nodes
{
TextBaseSize::TextBaseSize() noexcept : text_{}, value_{}
{}

TextBaseSize::TextBaseSize(char const ch, size_type const size) :
    text_{str::fromCharAndSize(ch, size)}, value_{}
{}

TextBaseSize::TextBaseSize(str text) : text_{htps::move(text)}, value_{}
{}

TextBaseSize::TextBaseSize(vector2df size) : text_{}, value_{htps::move(size)}
{}

TextBaseSize::TextBaseSize(str text, vector2df size) :
    text_{htps::move(text)}, value_{htps::move(size)}
{}

bool TextBaseSize::operator==(TextBaseSize const& rhs) const noexcept
{
    return text_ == rhs.text_ && value_ == rhs.value_;
}

str const& TextBaseSize::text() const noexcept
{
    return text_;
}

vector2df TextBaseSize::value() const noexcept
{
    return value_;
}

}  // namespace haf::scene::nodes
