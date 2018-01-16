#pragma once

#ifndef PARPAR_LIB_INCLUDE_HPP__
#define PARPAR_LIB_INCLUDE_HPP__

#include <string>
#include <vector>
#include <tuple>

namespace parpar
{
    class ParametersParser
    {
    private:

        enum class ParserErrorCodes
        {
            NoError,
            EmptyParameter,
            OptionWithoutEqual,
            EmptyOptionName,
            EmptyOptionValue
        };
        struct ParserError
        {
            ParserErrorCodes errorCode{ParserErrorCodes::NoError};
            unsigned int paramIndex{};
        };

        enum class ParameterType
        {
            Positional,
            Switch,
            Option
        };

        ParametersParser() = default;

        /// Method that returns the type of a parameter.
        /// @see ParameterType
        /// @param param The string representation of the parameter
        /// @return The enum value of the parameter parameter.
        static ParameterType getParameterType(const std::string &param)
        {
            if (param[0] == '-') {
                if (param[1] == '-') {
                return ParameterType::Switch;
                }
                return ParameterType::Option;
            }
            return ParameterType::Positional;
        }

        using CheckOptionParameterReturnValue
            = std::pair<ParserErrorCodes,std::pair<std::string,std::string>>;

        static CheckOptionParameterReturnValue make_from_error(ParserErrorCodes pec)
        {
            return CheckOptionParameterReturnValue({pec,{}});
        }

        /// Method that given a parameter assumed as option,
        /// checks if it is welll formed.
        /// @param param Parameter string to be checked.
        /// @return A tuple with an error code and two strings.
        /// If the error code is no error, the two strings are filled with
        /// name and value.
        static CheckOptionParameterReturnValue
            checkOptionParameter(const std::string &param)
        {
            // Find '=' sign
            const int equalSign(param.find_first_of('='));

            if (equalSign != std::string::npos)
            {
                if (equalSign != 0)
                {
                    const std::string name(param.substr(0,equalSign-1));
                    const std::string value(param.substr(equalSign+1));

                    if (name.empty())
                    {
                        return (ParserErrorCodes::EmptyOptionName);
                    }
                    if (value.empty())
                    {
                        return {ParserErrorCodes::EmptyOptionValue};
                    }
                    return {ParserErrorCodes::NoError, std::move(name), std::move(value) };
                }
                return {ParserErrorCodes::EmptyOptionName};
            }
            // No '=' found
            return {ParserErrorCodes::OptionWithoutEqual};
        }

        inline ParametersParser(int argc, char *argv[])
        {
            for (int i=1;i<argc;++i) {
                std::string param(argv[i]);

                m_currentError.paramIndex = i - 1;
                if (!param.empty())
                {
                    auto type(getParameterType(param));
                    if (type == ParameterType::Option)
                    {
                        auto result(checkOptionParameter(param));
                        m_currentError.ParserError = std::get<0>(result);
                    }
                    //TODO: Store the parsed data
                    m_parameters.emplace_back(std::move(param));
                }
                else
                {
                    m_currentError = ParserError(ParserErrorCodes::EmptyParameter,i-1);
                }
            }
        }

    public:
        inline auto numParameters() const { return m_parameters.size(); }
        inline bool hasParameters() const { return !m_parameters.empty(); }
    private:
        std::vector<std::string> m_parameters;
        ParserError m_currentError;

        friend ParametersParser create(int argc, char *argv[]);
    };

    ParametersParser create(int argc, char *argv[])
    {
        return ParametersParser(argc, argv);
    }
}

#endif
