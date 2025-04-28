#include <haf/include/scene_components/text_base_size.hpp>

using namespace htps;
using namespace fmath;

namespace haf::scene
{
TextBaseSize::TextBaseSize() noexcept : m_text{}, m_value{}
{}

TextBaseSize::TextBaseSize(char const ch, size_type const size) :
m_text{str::fromCharAndSize(ch, size)}, m_value{}
{}

TextBaseSize::TextBaseSize(str text) : m_text{htps::move(text)}, m_value{}
{}

TextBaseSize::TextBaseSize(vector2df size) : m_text{}, m_value{htps::move(size)}
{}

TextBaseSize::TextBaseSize(str text, vector2df size) :
m_text{htps::move(text)}, m_value{htps::move(size)}
{}

bool TextBaseSize::operator==(TextBaseSize const& rhs) const noexcept
{
    return m_text == rhs.m_text && m_value == rhs.m_value;
}

str const& TextBaseSize::text() const noexcept
{
    return m_text;
}

vector2df TextBaseSize::value() const noexcept
{
    return m_value;
}

}  // namespace haf::scene
