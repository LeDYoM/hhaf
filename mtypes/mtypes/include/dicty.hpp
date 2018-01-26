#pragma once

#ifndef MTYPES_DICTY_INCLUDE_HPP
#define MTYPES_DICTY_INCLUDE_HPP

#include "types.hpp"

namespace lib
{
    class Dictionary
    {
    public:
        bool add(str name, str value, const bool overwrite = true)
        {
            return std::get<1>(addInternal(name, value));
        }
    private:
        template <typename T1, typename T2>
        constexpr decltype(auto) addInternal(T1&& t1, T2&& t2, const bool overwrite = true)
        {
            if (overwrite) {
                return m_data.insert_or_assign(std::forward<T1>(t1),std::forward<T2>(t2));
            } else {
                return m_data.try_emplace(std::forward<T1>(t1),std::forward<T2>(t2));
            }
        }

        map<str,str> m_data;
    };
}

#endif
