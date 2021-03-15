#ifndef MTPS_STR_INCLUDE_HPP
#define MTPS_STR_INCLUDE_HPP

#include "vector.hpp"
#include "types.hpp"

#include <sstream>
#include <type_traits>
#include <algorithm>
#include <cctype>

namespace mtps
{
// template <typename char_type = char, typename Container = vector>
class str
{
public:
    using char_type       = char;
    using reference       = char_type&;
    using const_reference = const char_type&;
    using iterator        = char_type*;
    using const_iterator  = const char_type*;

private:
    vector<char_type> m_data;

public:
    constexpr str() noexcept : m_data{} {}

    constexpr str(str&&) noexcept = default;
    str& operator=(str&&) noexcept = default;

    constexpr str(const str& n) = default;
    constexpr str& operator=(const str& rhs) = default;

    template <size_type N>
    constexpr str(const char_type (&a)[N]) noexcept : m_data(a, N)
    {}

    constexpr str(const char_type* n, const size_type N) noexcept :
        m_data(n, N + 1)
    {}

    explicit str(const char_type* n) noexcept : str(n, _str_len(n)) {}

    constexpr str(const_iterator _begin, const_iterator _end) :
        str(_begin, (_end - _begin) + 1U)
    {}

    str& operator=(const char_type* n) noexcept
    {
        *this = str(n, _str_len(n));
        return *this;
    }

    inline static str to_str(const u64 n)
    {
        return str{std::to_string(n).c_str()};
    }

    inline static str to_str(const s64 n)
    {
        return str{std::to_string(n).c_str()};
    }

    inline static str to_str(const u32 n)
    {
        return str{std::to_string(n).c_str()};
    }

    inline static str to_str(const s32 n)
    {
        return str{std::to_string(n).c_str()};
    }
    inline static str to_str(const f32 n)
    {
        return str{std::to_string(n).c_str()};
    }
    inline static str to_str(const f64 n)
    {
        return str{std::to_string(n).c_str()};
    }

    template <typename T>
    bool is() const
    {
        T temp;
        return convert(temp);
    }

    constexpr size_t _str_len(const char_type* const p_str) noexcept
    {
        const str::char_type* p_str_copy{p_str};
        while (*p_str_copy)
            ++p_str_copy;
        return p_str_copy - p_str;
    }

    vector<str> split(const char_type separator) const
    {
        vector<str> result;

        str tok;
        auto _cend(cend());

        for (auto _cbegin(cbegin()); _cbegin != _cend; ++_cbegin)
        {
            str::char_type const ch = *_cbegin;
            if (ch == separator)
            {
                result.emplace_back(std::move(tok));
                tok = str();
            }
            else
            {
                tok.append_char(*_cbegin);
            }
        }

        result.emplace_back(std::move(tok));
        return result;
    }

    inline bool starts_with(const str& prefix) const noexcept
    {
        if (size() < prefix.size())
        {
            return false;
        }

        return (substr(0, prefix.size()) == prefix);
    }

    inline bool ends_with(const str& prefix) const noexcept
    {
        if (size() < prefix.size())
        {
            return false;
        }

        return (substr(size() - prefix.size()) == prefix);
    }

    str substr(size_type start, size_type len = npos) const
    {
        if (start >= size() || len < 1)
            return "";

        str temp;
        while (start < size() && len > 0)
        {
            if (m_data[start] != 0)
            {
                temp.m_data.push_back(m_data[start]);
            }
            ++start;
            --len;
        }

        temp.m_data.push_back(0);
        return temp;
    }

    constexpr str& append() { return *this; }

    str& append(const str& n)
    {
        m_data.pop_back();
        m_data.insert(n.m_data);
        return *this;
    }

    template <size_type N>
    constexpr str& append(const char_type (&n)[N])
    {
        append(str(std::forward<const char_type(&)[N]>(n)));
        return *this;
    }

    str& append(const char_type* n)
    {
        append(str(n));
        return *this;
    }

    str& append(const u64 n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(const s64 n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(const u32 n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(const s32 n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(const f32 n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(const f64 n)
    {
        append(to_str(n));
        return *this;
    }

    str& append_char(const char_type n)
    {
        const char_type temp[2U] = {n, 0U};
        return append(temp);
    }

    template <typename T>
    bool convert(T& n) const
    {
        std::istringstream iss(c_str());
        iss >> n;
        return (iss.eof() && !iss.fail());
    }

    template <typename T>
    [[nodiscard]] pair<bool, T> convert() const
    {
        T value;
        return {convert(value), value};
    }

    template <typename T>
    [[nodiscard]] T convertOrDefault() const
    {
        T value;
        convert(value);
        return value;
    }

    template <typename T>
    str& operator+=(T&& source)
    {
        return append(std::forward<T>(source));
    }

    str& operator+=(const str& source) { return append(source); }

    constexpr size_type size() const noexcept
    {
        return m_data.empty() ? 0 : m_data.size() - 1;
    }

    inline void ltrim()
    {
        if (!empty())
        {
            for (size_type index = 0U; index < size(); ++index)
            {
                if (!std::isspace(static_cast<char_type>(m_data[index])))
                {
                    *this = substr(index);
                    return;
                }
            }
            *this = "";
        }
    }

    constexpr size_type find(const char_type ch) const noexcept
    {
        const auto it(m_data.cfind(ch));
        return ((it == m_data.cend()) ? npos : std::distance(cbegin(), it));
    }

    // trim from end (in place)
    inline void rtrim()
    {
        if (!empty())
        {
            for (size_type index = size() - 1; index > 0; --index)
            {
                if (!std::isspace(static_cast<unsigned char>(m_data[index])))
                {
                    *this = substr(0U, index + 1U);
                    return;
                }
            }

            *this = (std::isspace(static_cast<unsigned char>(m_data[0U])))
                ? ""
                : substr(0U, 1U);
        }
    }

    // trim from both ends (in place)
    inline void trim()
    {
        ltrim();
        rtrim();
    }

    // TO DO: Change them by using, eg.
    // using vector<T>::begin();
    constexpr reference operator[](const size_type index) noexcept
    {
        return m_data[index];
    }
    constexpr const_reference operator[](const size_type index) const noexcept
    {
        return m_data[index];
    }
    constexpr iterator begin() noexcept { return m_data.begin(); }
    constexpr const_iterator begin() const noexcept { return m_data.begin(); }
    constexpr const_iterator cbegin() const noexcept { return m_data.cbegin(); }
    constexpr iterator end() noexcept { return m_data.begin() + size(); }
    constexpr const_iterator end() const noexcept
    {
        return m_data.begin() + size();
    }
    constexpr const_iterator cend() const noexcept
    {
        return m_data.cbegin() + size();
    }

    constexpr char_type const* c_str() const noexcept
    {
        return m_data.empty() ? "" : m_data.cbegin();
    }
    constexpr bool empty() const noexcept { return size() == 0; }

    constexpr auto find_first_of(
        const vector<char_type>& chValue) const noexcept
    {
        const auto it(m_data.find_first_of(chValue));
        return (it == m_data.cend()) ? str::npos : std::distance(cbegin(), it);
    }

    inline auto find_first_of(const char_type chValue) const noexcept
    {
        return find_first_of(vector<char_type>{chValue});
    }

    template <typename T>
    constexpr bool operator>>(T& n) const
    {
        if constexpr (std::is_enum_v<T>)
        {
            std::underlying_type_t<T> tmp{};
            const bool result{convert(tmp)};
            n = static_cast<T>(tmp);
            return result;
        }
        else if constexpr (std::is_same_v<T, str>)
        {
            n = *this;
            return true;
        }
        else
        {
            return convert(n);
        }
    }

    static const size_type npos = static_cast<size_type>(-1);

    constexpr bool operator==(const str& rhs) const noexcept
    {
        return m_data == rhs.m_data;
    }

    constexpr bool operator!=(const str& rhs) const noexcept
    {
        return !(m_data == rhs.m_data);
    }

    template <size_type N>
    constexpr bool operator==(const char_type (&a)[N]) const noexcept
    {
        if (size() != (N - 1))
            return false;

        size_type counter{0};
        for (const auto c : m_data)
        {
            if (c != a[counter])
                return false;
            ++counter;
        }
        return true;
    }

    template <size_type N>
    constexpr bool operator!=(const char_type (&a)[N]) const noexcept
    {
        return !(this->operator==(a));
    }

    constexpr bool operator==(const str::char_type* a) const noexcept
    {
        size_type counter{0};
        for (; counter < size() && a[counter] != 0; ++counter)
        {
            if (m_data[counter] != a[counter])
            {
                return false;
            }
        }
        return counter == size() && a[counter] == 0;
    }

    constexpr bool operator!=(const str::char_type* a) const noexcept
    {
        return !(*this == a);
    }

    template <typename T>
    constexpr str& operator<<(const T& n)
    {
        return append(n);
    }

    template <size_type N>
    friend constexpr bool operator==(const char_type (&a)[N],
                                     const str& rhs) noexcept;
    template <size_type N>
    friend constexpr bool operator!=(const char_type (&a)[N],
                                     const str& rhs) noexcept;

    friend constexpr bool operator==(const char_type* a,
                                     const str& rhs) noexcept;
    friend constexpr bool operator!=(const char_type* a,
                                     const str& rhs) noexcept;

    constexpr bool operator<(const str& rhs) const noexcept
    {
        size_type i{0};
        while (i < size() && i < rhs.size())
        {
            if (m_data[i] < rhs[i])
            {
                return true;
            }
            else if (m_data[i] > rhs[i])
            {
                return false;
            }
            ++i;
        }
        return size() < rhs.size();
    }
};

inline str operator+(const str& lhs, const str& rhs) noexcept
{
    return str(lhs).append(rhs);
}

template <size_type N>
constexpr bool operator==(const str::char_type (&a)[N], const str& rhs) noexcept
{
    return rhs == a;
}

template <size_type N>
constexpr bool operator!=(const str::char_type (&a)[N], const str& rhs) noexcept
{
    return rhs != a;
}

constexpr bool operator==(const str::char_type* a, const str& rhs) noexcept
{
    return rhs == a;
}

constexpr bool operator!=(const str::char_type* a, const str& rhs) noexcept
{
    return rhs != a;
}

template <typename... Args>
constexpr str make_str(Args&&... args)
{
    str t;
    make_str_internal(t, std::forward<Args>(args)...);
    return t;
}

template <typename T>
constexpr str make_str(T&& arg)
{
    str t;
    make_str_internal(t, std::forward<T>(arg));
    return t;
}

template <>
inline str make_str(u64&& n)
{
    return str::to_str(std::move(n));
}
template <>
inline str make_str(s64&& n)
{
    return str::to_str(std::move(n));
}
template <>
inline str make_str(u32&& n)
{
    return str::to_str(std::move(n));
}
template <>
inline str make_str(s32&& n)
{
    return str::to_str(std::move(n));
}
template <>
inline str make_str(f32&& n)
{
    return str::to_str(std::move(n));
}
template <>
inline str make_str(f64&& n)
{
    return str::to_str(std::move(n));
}

template <typename T, typename... Args>
constexpr void make_str_internal(str& buffer, T&& arg, Args&&... args)
{
    make_str_internal(buffer, std::forward<T>(arg));
    make_str_internal(buffer, std::forward<Args>(args)...);
}

template <typename T>
constexpr void make_str_internal(str& buffer, T&& arg)
{
    buffer << std::forward<T>(arg);
}

static_assert(std::is_move_constructible_v<str>, "str must be movable");
static_assert(std::is_move_assignable_v<str>, "str must be movable assignable");
static_assert(std::is_default_constructible_v<str>,
              "str must be default constructible");
static_assert(std::is_copy_constructible_v<str>,
              "str must be copy constructible");
using string_vector = vector<str>;

template<size_t N>
struct cestr
{
    constexpr cestr(const char (&str)[N])
    {
        std::copy_n(str, N, value);
    }
    
    char value[N];
};
}  // namespace mtps

#endif
