#ifndef HTPS_BASIC_STR_INCLUDE_HPP
#define HTPS_BASIC_STR_INCLUDE_HPP

#include "vector.hpp"
#include "str_view.hpp"
#include "types.hpp"

#include <sstream>
#include <type_traits>
#include <algorithm>
#include <cctype>

namespace htps
{
template <typename char_type>
class basic_str
{
public:
    using value_type = char_type;   //< Type of the characters used
    using reference  = char_type&;  //< Type reference of the characters used
    using const_reference =
        char_type const&;         //< Type of a const reference to a char_type;
    using iterator = char_type*;  //< Iterator value of the string;
    using const_iterator =
        char_type const*;  //< Const iterator type of the string

private:
    vector<char_type> data_;

public:
    constexpr basic_str() noexcept : data_{} {}

    template <size_type N>
    constexpr basic_str(const char_type (&a)[N]) : data_(a, N)
    {}

    constexpr basic_str(const_iterator const n, size_type const N) :
        data_(n, N + 1)
    {}

    constexpr basic_str(char_type const* const n) :
        basic_str(n, detail::_str_len(n))
    {}

    constexpr basic_str(const_iterator _begin, const_iterator _end) :
        basic_str(_begin, (_end - _begin) + 1U)
    {}

    constexpr basic_str(basic_str&&) noexcept = default;
    basic_str& operator=(basic_str&&) noexcept = default;

    constexpr basic_str(basic_str const& n) = default;
    constexpr basic_str& operator=(basic_str const& rhs) = default;

    basic_str& operator=(char_type const* const n)
    {
        *this = basic_str(n, detail::_str_len(n));
        return *this;
    }

    void swap(basic_str& other) { data_.swap(other.data_); }

    static basic_str to_str(u64 const n)
    {
        return basic_str{std::to_string(n).c_str()};
    }

    static basic_str to_str(s64 const n)
    {
        return basic_str{std::to_string(n).c_str()};
    }

    static basic_str to_str(u32 const n)
    {
        return basic_str{std::to_string(n).c_str()};
    }

    static basic_str to_str(s32 const n)
    {
        return basic_str{std::to_string(n).c_str()};
    }

    static basic_str to_str(f32 const n)
    {
        return basic_str{std::to_string(n).c_str()};
    }

    static basic_str to_str(f64 const n)
    {
        return basic_str{std::to_string(n).c_str()};
    }

    template <typename T>
    bool is() const
    {
        T temp;
        return convert(temp);
    }

    vector<basic_str> split(char_type const separator) const
    {
        vector<basic_str> result;

        basic_str tok;

        for (auto const it : *this)
        {
            if (it == separator)
            {
                result.emplace_back(std::move(tok));
                tok = basic_str();
            }
            else
            {
                tok.push_back(it);
            }
        }

        result.emplace_back(std::move(tok));
        return result;
    }

    bool starts_with(basic_str const& prefix) const noexcept
    {
        return has_in(prefix, 0U);
    }

    bool ends_with(basic_str const& prefix) const noexcept
    {
        return has_in(prefix, size() - prefix.size());
    }

    bool has_in(basic_str const& prefix,
                       size_type const start_position) const noexcept
    {
        if (size() < prefix.size() || start_position > size())
        {
            return false;
        }

        return (substr(start_position, prefix.size()) == prefix);
    }

    size_type has(basic_str const& sub_str) const noexcept
    {
        if (size() < sub_str.size())
        {
            return npos;
        }

        if (sub_str.empty())
        {
            return 0U;
        }

        auto const size_to_check{size() - (sub_str.size() - 1U)};

        for (size_type i{0U}; i < size_to_check; ++i)
        {
            if (has_in(sub_str, i))
            {
                return i;
            }
        }
        return npos;
    }

    basic_str substr(size_type start, size_type len = npos) const
    {
        if (start >= size() || len < 1U)
        {
            return "";
        }

        basic_str temp;
        while (start < size() && len > 0U)
        {
            if (data_[start] != 0)
            {
                temp.data_.push_back(data_[start]);
            }
            ++start;
            --len;
        }

        temp.data_.push_back(0);
        return temp;
    }

    constexpr basic_str& append() { return *this; }

    basic_str& append(basic_str const& n)
    {
        data_.pop_back();
        data_.insert(n.data_);
        return *this;
    }

    basic_str& append(basic_str&& n)
    {
        data_.pop_back();
        data_.insert(std::move(n.data_));
        return *this;
    }

    template <size_type N>
    constexpr basic_str& append(char_type const (&n)[N])
    {
        append(str(std::forward<char_type const(&)[N]>(n)));
        return *this;
    }

    basic_str& append(char_type const* const n)
    {
        append(basic_str(n));
        return *this;
    }

    basic_str& append(u64 const n)
    {
        append(to_str(n));
        return *this;
    }

    basic_str& append(s64 const n)
    {
        append(to_str(n));
        return *this;
    }

    basic_str& append(u32 const n)
    {
        append(to_str(n));
        return *this;
    }

    basic_str& append(s32 const n)
    {
        append(to_str(n));
        return *this;
    }

    basic_str& append(f32 const n)
    {
        append(to_str(n));
        return *this;
    }

    basic_str& append(f64 const n)
    {
        append(to_str(n));
        return *this;
    }

    basic_str& push_back(char_type const n)
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
    basic_str& operator+=(T&& source)
    {
        return append(std::forward<T>(source));
    }

    basic_str& operator+=(basic_str const& source) { return append(source); }

    basic_str operator+(basic_str<value_type> const& rhs) const
    {
        return basic_str<value_type>(*this).append(rhs);
    }

    basic_str operator+(char_type const* const rhs) const
    {
        return basic_str<value_type>(*this).append(rhs);
    }

    constexpr size_type size() const noexcept
    {
        return data_.empty() ? 0 : (data_.size() - 1U);
    }

    void ltrim()
    {
        if (!empty())
        {
            for (size_type index{0U}; index < size(); ++index)
            {
                if (!std::isspace(static_cast<char_type>(data_[index])))
                {
                    *this = substr(index);
                    return;
                }
            }
            data_.clear();
        }
    }

    constexpr size_type find(char_type const ch) const noexcept
    {
        const auto it(data_.cfind(ch));
        return ((it == data_.cend()) ? npos : std::distance(cbegin(), it));
    }

    // trim from end (in place)
    void rtrim()
    {
        if (!empty())
        {
            for (size_type index{size() - 1U}; index > 0U; --index)
            {
                if (!std::isspace(static_cast<unsigned char>(data_[index])))
                {
                    *this = substr(0U, index + 1U);
                    return;
                }
            }

            *this = (std::isspace(static_cast<unsigned char>(data_[0U])))
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
        return data_[index];
    }

    constexpr const_reference operator[](size_type const index) const noexcept
    {
        return data_[index];
    }

    constexpr auto capacity() const noexcept { return data_.capacity(); }
    constexpr iterator begin() noexcept { return data_.begin(); }
    constexpr const_iterator begin() const noexcept { return data_.begin(); }
    constexpr const_iterator cbegin() const noexcept { return data_.cbegin(); }
    constexpr iterator end() noexcept { return data_.begin() + size(); }
    constexpr const_iterator end() const noexcept
    {
        return data_.begin() + size();
    }

    constexpr const_iterator cend() const noexcept
    {
        return data_.cbegin() + size();
    }

    constexpr char_type const* c_str() const noexcept
    {
        return data_.empty() ? "" : data_.cbegin();
    }

    constexpr bool empty() const noexcept { return size() == 0; }

    constexpr auto find_first_of(
        vector<char_type> const& chValue) const noexcept
    {
        const auto it{data_.find_first_of(chValue)};
        return (it == data_.cend()) ? basic_str::npos
                                    : std::distance(cbegin(), it);
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
        else if constexpr (std::is_same_v<T, basic_str>)
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

    constexpr bool operator==(basic_str const& rhs) const noexcept
    {
        return data_ == rhs.data_;
    }

    constexpr bool operator!=(basic_str const& rhs) const noexcept
    {
        return !(data_ == rhs.data_);
    }

    constexpr bool operator==(char_type const* const rhs) const noexcept
    {
        size_type counter{0U};
        for (; counter < size() && rhs[counter] != 0U; ++counter)
        {
            if (data_[counter] != rhs[counter])
            {
                return false;
            }
        }

        return (counter == size() && rhs[counter] == 0);
    }

    constexpr bool operator!=(char_type const* const a) const noexcept
    {
        return !(*this == a);
    }

    template <typename T>
    constexpr basic_str& operator<<(T const& n)
    {
        return append(n);
    }

    constexpr bool operator<(const basic_str& rhs) const noexcept
    {
        for (size_type i{0U}; i < size() && i < rhs.size(); ++i)
        {
            if (data_[i] < rhs[i])
            {
                return true;
            }
            else if (data_[i] > rhs[i])
            {
                return false;
            }
        }
        return size() < rhs.size();
    }
};

template <typename T, typename value_type>
basic_str<value_type> operator+(T&& lhs, basic_str<value_type> const& rhs)
{
    return basic_str<value_type>(std::forward<T>(lhs)).append(rhs);
}

template <typename char_value>
constexpr bool operator==(char_value const* const lhs,
                          basic_str<char_value> const& rhs) noexcept
{
    return rhs == lhs;
}

template <typename char_value>
constexpr bool operator!=(char_value const* const lhs,
                          basic_str<char_value> const& rhs) noexcept
{
    return rhs != lhs;
}

template <typename char_value, typename T, typename... Args>
constexpr void make_basic_str_internal(basic_str<char_value>& buffer,
                                       T&& arg,
                                       Args&&... args)
{
    make_basic_str_internal(buffer, std::forward<T>(arg));
    make_basic_str_internal(buffer, std::forward<Args>(args)...);
}

template <typename char_value, typename T>
constexpr void make_basic_str_internal(basic_str<char_value>& buffer, T&& arg)
{
    buffer << std::forward<T>(arg);
}

template <typename char_value, typename... Args>
constexpr basic_str<char_value> make_basic_str(Args&&... args)
{
    basic_str<char_value> t;
    make_basic_str_internal(t, std::forward<Args>(args)...);
    return t;
}

template <typename char_value, typename T>
constexpr basic_str<char_value> make_basic_str(T&& arg)
{
    basic_str<char_value> t;
    make_basic_str_internal(t, std::forward<T>(arg));
    return t;
}

template <typename char_value>
inline basic_str<char_value> make_basic_str(u64&& n)
{
    return basic_str<char_value>::to_str(std::move(n));
}

template <typename char_value>
inline basic_str<char_value> make_basic_str(s64&& n)
{
    return basic_str<char_value>::to_str(std::move(n));
}

template <typename char_value>
inline basic_str<char_value> make_basic_str(u32&& n)
{
    return basic_str<char_value>::to_str(std::move(n));
}

template <typename char_value>
inline basic_str<char_value> make_basic_str(s32&& n)
{
    return basic_str<char_value>::to_str(std::move(n));
}

template <typename char_value>
inline basic_str<char_value> make_basic_str(f32&& n)
{
    return basic_str<char_value>::to_str(std::move(n));
}

template <typename char_value>
inline basic_str<char_value> make_basic_str(f64&& n)
{
    return basic_str<char_value>::to_str(std::move(n));
}

}  // namespace htps

#endif
