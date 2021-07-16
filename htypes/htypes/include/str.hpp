#ifndef MTPS_STR_INCLUDE_HPP
#define MTPS_STR_INCLUDE_HPP

#include "vector.hpp"
#include "str_view.hpp"
#include "types.hpp"

#include <sstream>
#include <type_traits>
#include <algorithm>
#include <cctype>

namespace htps
{
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

    constexpr str(char_type const* const n, size_type const N) noexcept :
        m_data(n, N + 1)
    {}

    explicit str(char_type const* const n) noexcept : str(n, detail::_str_len(n)) {}

    constexpr str(const_iterator _begin, const_iterator _end) :
        str(_begin, (_end - _begin) + 1U)
    {}

    str& operator=(const char_type* n)
    {
        *this = str(n, detail::_str_len(n));
        return *this;
    }

    void swap(str& other) { m_data.swap(other.m_data); }

    static str to_str(u64 const n) { return str{std::to_string(n).c_str()}; }

    static str to_str(s64 const n) { return str{std::to_string(n).c_str()}; }

    static str to_str(u32 const n) { return str{std::to_string(n).c_str()}; }

    static str to_str(s32 const n) { return str{std::to_string(n).c_str()}; }

    static str to_str(f32 const n) { return str{std::to_string(n).c_str()}; }

    static str to_str(f64 const n) { return str{std::to_string(n).c_str()}; }

    template <typename T>
    bool is() const
    {
        T temp;
        return convert(temp);
    }

    vector<str> split(char_type const separator) const
    {
        vector<str> result;

        str tok;

        for (auto const it : *this)
        {
            if (it == separator)
            {
                result.emplace_back(std::move(tok));
                tok = str();
            }
            else
            {
                tok.push_back(it);
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
        if (start >= size() || len < 1U)
        {
            return "";
        }

        str temp;
        while (start < size() && len > 0U)
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

    str& append(str const& n)
    {
        m_data.pop_back();
        m_data.insert(n.m_data);
        return *this;
    }

    str& append(str&& n)
    {
        m_data.pop_back();
        m_data.insert(std::move(n.m_data));
        return *this;
    }

    template <size_type N>
    constexpr str& append(const char_type (&n)[N])
    {
        append(str(std::forward<const char_type(&)[N]>(n)));
        return *this;
    }

    str& append(char_type const* const n)
    {
        append(str(n));
        return *this;
    }

    str& append(u64 const n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(s64 const n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(u32 const n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(s32 const n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(f32 const n)
    {
        append(to_str(n));
        return *this;
    }

    str& append(f64 const n)
    {
        append(to_str(n));
        return *this;
    }

    str& push_back(char_type const n)
    {
        char_type const temp[2U] = {n, 0U};
        return append(std::move(temp));
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
    void rtrim()
    {
        if (!empty())
        {
            for (size_type index{size() - 1U}; index > 0U; --index)
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
    void trim()
    {
        ltrim();
        rtrim();
    }

    // TO DO: Change them by using, eg.
    // using vector<T>::begin();
    constexpr reference operator[](size_type const index) noexcept
    {
        return m_data[index];
    }

    constexpr const_reference operator[](size_type const index) const noexcept
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
        vector<char_type> const& chValue) const noexcept
    {
        const auto it{m_data.find_first_of(chValue)};
        return (it == m_data.cend()) ? str::npos : std::distance(cbegin(), it);
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
        {
            return false;
        }

        size_type counter{0U};
        for (const auto c : m_data)
        {
            if (c != a[counter])
            {
                return false;
            }
            ++counter;
        }
        return true;
    }

    template <size_type N>
    constexpr bool operator!=(char_type const (&rhs)[N]) const noexcept
    {
        return !(this->operator==(std::forward<char_type const(&)[N]>(rhs)));
    }

    constexpr bool operator==(str::char_type const* const rhs) const noexcept
    {
        size_type counter{0};
        for (; counter < size() && rhs[counter] != 0U; ++counter)
        {
            if (m_data[counter] != rhs[counter])
            {
                return false;
            }
        }

        return (counter == size() && rhs[counter] == 0);
    }

    constexpr bool operator!=(str::char_type const* const a) const noexcept
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
        size_type i{0U};
        for (; i < size() && i < rhs.size(); ++i)
        {
            if (m_data[i] < rhs[i])
            {
                return true;
            }
            else if (m_data[i] > rhs[i])
            {
                return false;
            }
        }
        return size() < rhs.size();
    }
};

inline str operator+(str const& lhs, str const& rhs)
{
    return str(lhs).append(rhs);
}

template <size_type N>
constexpr bool operator==(str::char_type const (&lhs)[N],
                          str const& rhs) noexcept
{
    return rhs == lhs;
}

template <size_type N>
constexpr bool operator!=(str::char_type const (&lhs)[N],
                          str const& rhs) noexcept
{
    return rhs != lhs;
}

constexpr bool operator==(str::char_type const* const lhs,
                          str const& rhs) noexcept
{
    return rhs == lhs;
}

constexpr bool operator!=(str::char_type const* const lhs,
                          str const& rhs) noexcept
{
    return rhs != lhs;
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

}  // namespace htps

#endif
