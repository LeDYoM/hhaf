#pragma once

#ifndef MTYPES_DICTY_INCLUDE_HPP
#define MTYPES_DICTY_INCLUDE_HPP

namespace lib
{
    template <typename str_type>
    class BasicDictionary
    {
    public:
        using element = std::pair<str_type, str_type>;
        using content = vector<element>;
        using iterator = content::iterator;
        using const_iterator = content::const_iterator;

        bool add(std::initializer_list<element> eList, const bool overwrite=true)
        {
            bool result{true};
            for (element&& elems : eList) {
                result &= add(elems.first, elems.second, overwrite);
            }
            return result;
        }

        bool add(str_type key, str_type value, const bool overwrite = true)
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

        void clear() {
            m_data.clear();
        }


    private:
        const_iterator find(const str_type &key) const noexcept {
            for (const auto& element : m_data) {
                if (element.first == key) {
                    return &element;
                }
            }
            return m_data.cend();
        }

        iterator find(const str_type &key) noexcept {
            for (auto& element : m_data) {
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
