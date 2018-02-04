#pragma once

#ifndef MTYPES_DICTY_INCLUDE_HPP
#define MTYPES_DICTY_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "vector.hpp"

namespace lib
{
    class BasicDictionary
    {
    public:
        using element = std::pair<str, str>;
        using content = vector<element>;
        using iterator = content::iterator;
        using const_iterator = content::const_iterator;

        BasicDictionary() = default;

        BasicDictionary(std::initializer_list<element> eList)
            : m_data{ std::move(eList) } {}

        BasicDictionary(const content &eList)
            : m_data{ std::move(eList) } {}

        bool add(const content &eList, const bool overwrite = true)
        {
            bool result{ true };
            for (const element& elems : eList) {
                result &= add(elems.first, elems.second, overwrite);
            }
            return result;
        }

        bool add(std::initializer_list<element> eList, const bool overwrite = true)
        {
            bool result{true};
            for (const element& elems : eList) {
                result &= add(elems.first, elems.second, overwrite);
            }
            return result;
        }

        bool add(str key, str value, const bool overwrite = true)
        {
            auto it(find(key));

            if (it == m_data.cend()) {
                m_data.emplace_back(std::move(key), std::move(value));
                return true;
            }
            else if (overwrite) {
                (*it) = element(key, value);
                return true;
            }
            return false;
        }

        constexpr void clear() {
            m_data.clear();
        }

        const content &data() const noexcept {
            return m_data;
        }

    private:
        constexpr const_iterator find(const str &key) const noexcept {
            for (auto &element : m_data) {
                if (element.first == key) {
                    return &element;
                }
            }
            return m_data.cend();
        }

        constexpr iterator find(const str &key) noexcept {
            for (auto &element : m_data) {
                if (element.first == key) {
                    return &element;
                }
            }
            return m_data.end();
        }

        content m_data;
    };
}

#endif
