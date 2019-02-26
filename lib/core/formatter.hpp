#pragma once

#ifndef LIB_FORMATTER_INCLUDE_HPP
#define LIB_FORMATTER_INCLUDE_HPP

#include <mtypes/include/streamin.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/str.hpp>

namespace lib::core
{
    struct Token
    {
        enum class Type
        {
            OpenObject = 0U,
            CloseObject
        };
    };

    class Parser final
    {
    public:
        explicit Parser(SerializationStreamIn stream)
            : stream_{ stream } {}

        bool parse()
        {
            for (auto parser_state : parser_states)
            {
                str token;
                stream_ >> token;
            }
            return true;
        }

    private:
        vector<sptr<Token>> parser_states;
        SerializationStreamIn &stream_;
    };
}

#endif
