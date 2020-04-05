#pragma once

#ifndef MTYPES_DICTIONARY_INCLUDE_HPP
#define MTYPES_DICTIONARY_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "vector.hpp"

namespace mtps
{
    class Object;

	/// This class contains a group of keys and their associated values.
	/// It is used as a component for the @Object class.
    template <typename T>
    class Dictionary
    {
    public:
        using value_type = T;
        using element = pair<str, value_type>;
        using content = vector<element>;
        using iterator = typename content::iterator;
        using const_iterator = typename content::const_iterator;

        /// Default constructor.
        constexpr Dictionary() = default;

        constexpr Dictionary(std::initializer_list<element> eList)
            : m_data{ std::move(eList) } {}

        constexpr Dictionary(const content &eList)
            : m_data{ std::move(eList) } {}

        constexpr iterator begin() noexcept { return m_data.begin(); }
        constexpr const_iterator begin() const noexcept{ return m_data.begin(); }
        constexpr iterator end() noexcept { return m_data.end(); }
        constexpr const_iterator end() const noexcept{ return m_data.end(); }
        constexpr const_iterator cbegin() const noexcept{ return m_data.begin(); }
        constexpr const_iterator cend() const noexcept{ return m_data.end(); }

        constexpr bool add(const content &eList, const bool overwrite = true)
        {
            bool result{ true };
            for (const element& elems : eList) 
            {
                result &= add(elems.first, elems.second, overwrite);
            }
            return result;
        }

        constexpr bool add(std::initializer_list<element> eList, const bool overwrite = true)
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

            if (it == m_data.end()) 
            {
                m_data.emplace_back(std::move(key), std::move(value));
                return true;
            }
            else if (overwrite)
            {
                (*it) = element(key, value);
                return true;
            }
            return false;
        }

        constexpr void clear() 
        {
            m_data.clear();
        }

        constexpr const content &data() const noexcept 
        {
            return m_data;
        }

        constexpr const_iterator find(const str &key) const noexcept 
        {
            for (auto &element : m_data) 
            {
                if (element.first == key) 
                {
                    return &element;
                }
            }
            return m_data.cend();
        }

        constexpr iterator find(const str &key) noexcept 
        {
            for (auto&& element : m_data) 
            {
                if (element.first == key) 
                {
                    return &element;
                }
            }
            return m_data.end();
        }

        constexpr bool exists(const str &key) const noexcept 
        {
            return find(key) != m_data.cend();
        }

        constexpr pair<bool,iterator> findChecked(const str&key) noexcept
        {
            auto iterator(find(key));
            return {iterator != m_data.end(), iterator};
        }

        constexpr pair<bool,const_iterator> findChecked(const str&key) const noexcept
        {
            const auto it(find(key));
            return {it != m_data.cend(), it};
        }

        constexpr size_type size() const noexcept 
        {
            return m_data.size();
        }

        constexpr bool empty() const noexcept
        {
            return m_data.empty();
        }

        constexpr bool operator==(const Dictionary &other) const noexcept 
        {
            if (m_data.size() == other.m_data.size()) 
            {
                for (size_type i = { 0U }; i < m_data.size(); ++i)
                {
                    if (m_data[i].first != other.m_data[i].first) 
                    {
                        return false;
                    }
                    else if (m_data[i].second != other.m_data[i].second) 
                    {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        constexpr bool operator!=(const Dictionary &other) const noexcept 
        {
            return !(*this == other);
        }

    private:
        content m_data;
    };
}

#endif
