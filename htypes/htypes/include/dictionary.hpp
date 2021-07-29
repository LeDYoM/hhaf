#ifndef HTYPES_DICTIONARY_INCLUDE_HPP
#define HTYPES_DICTIONARY_INCLUDE_HPP

#include <initializer_list>
#include "types.hpp"
#include "str.hpp"
#include "vector.hpp"

namespace htps
{
/**
 * @brief This class contains a group of keys and their associated values.
 * @tparam T Type of the values stored
 */
template <typename T>
class Dictionary final
{
public:
    using value_type     = T;
    using key            = str;
    using element        = pair<str, value_type>;
    using content        = vector<element>;
    using iterator       = typename content::iterator;
    using const_iterator = typename content::const_iterator;

    /**
     * @brief  Default constructor
     *
     */
    constexpr Dictionary() noexcept = default;

    constexpr Dictionary(std::initializer_list<element> eList) :
        data_{std::move(eList)}
    {}

    constexpr Dictionary(const content& eList) : data_{std::move(eList)} {}

    constexpr iterator begin() noexcept { return data_.begin(); }
    constexpr const_iterator begin() const noexcept { return data_.begin(); }
    constexpr iterator end() noexcept { return data_.end(); }
    constexpr const_iterator end() const noexcept { return data_.end(); }
    constexpr const_iterator cbegin() const noexcept { return data_.begin(); }
    constexpr const_iterator cend() const noexcept { return data_.end(); }

    constexpr bool add(const content& eList, const bool overwrite = true)
    {
        bool result{true};
        for (const element& elems : eList)
        {
            result &= add(elems.first, elems.second, overwrite);
        }
        return result;
    }

    constexpr bool add(std::initializer_list<element> eList,
                       const bool overwrite = true)
    {
        bool result{true};
        for (const element& elems : eList)
        {
            result &= add(elems.first, elems.second, overwrite);
        }
        return result;
    }

    constexpr bool add(str key, T value, const bool overwrite = true)
    {
        auto it(find(key));

        if (it == data_.end())
        {
            data_.emplace_back(std::move(key), std::move(value));
            return true;
        }
        else if (overwrite)
        {
            (*it) = element(key, value);
            return true;
        }
        return false;
    }

    constexpr void clear() { data_.clear(); }

    constexpr content const& data() const noexcept { return data_; }

    constexpr const_iterator find(str const& key) const noexcept
    {
        return data_.find_if(
            [&key](auto const& element) { return element.first == key; });
    }

    constexpr const_iterator cfind(str const& key) const noexcept
    {
        return find(key);
    }

    constexpr iterator find(const str& key) noexcept
    {
        return data_.find_if(
            [&key](auto const& element) { return element.first == key; });
    }

    constexpr bool exists(str const& key) const noexcept
    {
        return cfind(key) != data_.cend();
    }

    constexpr pair<bool, iterator> find_checked(str const& key) noexcept
    {
        auto const iterator(find(key));
        return {iterator != data_.cend(), iterator};
    }

    constexpr pair<bool, const_iterator> find_checked(
        str const& key) const noexcept
    {
        auto const it(cfind(key));
        return {it != data_.cend(), it};
    }

    constexpr pair<bool, const_iterator> cfind_checked(
        str const& key) const noexcept
    {
        return find_checked(key);
    }

    constexpr size_type size() const noexcept { return data_.size(); }

    constexpr bool empty() const noexcept { return data_.empty(); }

    constexpr bool operator==(Dictionary const& other) const noexcept
    {
        return data_ == other.data_;
    }

    constexpr bool operator!=(Dictionary const& other) const noexcept
    {
        return !(*this == other);
    }

private:
    content data_;
};
}  // namespace htps

#endif
