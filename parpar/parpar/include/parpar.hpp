#pragma once

#ifndef PARPAR_LIB_INCLUDE_HPP__
#define PARPAR_LIB_INCLUDE_HPP__

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

namespace parpar
{
    class ParametersParser
    {
    private:

        using PositionalParameter = std::string;
        using SwitchParameter = PositionalParameter;
        using OptionParameter = std::pair<const std::string, const std::string>;

        enum class SyntaxParserErrorCodes
        {
            NoError,
            OptionWithoutEqual,
            EmptyOptionName,
            EmptyOptionValue,

            // Exceptional cases, might never be reached
            EmptyParameter,
            UnknownParameterType

        };
        struct SintaxParserError
        {
            SyntaxParserErrorCodes errorCode{SyntaxParserErrorCodes::NoError};
            unsigned int paramIndex{};
        };

        enum class ParameterType
        {
            Positional,
            Switch,
            Option
        };

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

        using COptionResult
            = std::pair<SyntaxParserErrorCodes,std::pair<std::string,std::string>>;

        /// Method that given a parameter assumed as option,
        /// checks if it is well formed.
        /// @param param Parameter string to be checked.
        /// @return A tuple with an error code and two strings.
        /// If the error code is no error, the two strings are filled with
        /// name and value.
        static COptionResult checkOptionParameter(const std::string &param)
        {
            // Find '=' sign
            const auto equalSign(param.find_first_of('='));

            if (equalSign != std::string::npos)
            {
                if (equalSign != 0)
                {
                    const std::string name(param.substr(0,equalSign-1));
                    const std::string value(param.substr(equalSign+1));

                    if (name.empty())
                    {
                        return COptionResult(SyntaxParserErrorCodes::EmptyOptionName, {});
                    }
                    if (value.empty())
                    {
                        return COptionResult(SyntaxParserErrorCodes::EmptyOptionValue, {});
                    }
                    return COptionResult(SyntaxParserErrorCodes::NoError,
                        { std::move(name), std::move(value) });
                }
                return COptionResult(SyntaxParserErrorCodes::EmptyOptionName, {});
            }
            // No '=' found
            return COptionResult{ SyntaxParserErrorCodes::OptionWithoutEqual,{} };
        }

        inline ParametersParser(std::vector<std::string> argv)
        {
            for (decltype(argv.size()) i{1};i<argv.size();++i) {
                std::string param{std::move(argv[i])};

                if (!param.empty())
                {
                    switch (getParameterType(param))
                    {
                    case ParameterType::Positional:
                    {
                        m_positionalParameters.push_back(std::move(param));
                        m_syntaxErrors.push_back(SyntaxParserErrorCodes::NoError);
                    }
                    break;
                    case ParameterType::Switch:
                    {
                        m_switchParameters.push_back(std::move(param));
                        m_syntaxErrors.push_back(SyntaxParserErrorCodes::NoError);
                    }
                    break;
                    case ParameterType::Option:
                    {
                        auto result(checkOptionParameter(param));
                        m_syntaxErrors.push_back(std::get<0>(result));
                        m_optionParameters.emplace_back(
                            std::get<1>(result).first,
                            std::get<1>(result).second);
                    }
                    break;

                    default:
                    {
                        m_positionalParameters.push_back(std::move(param));
                        m_syntaxErrors.push_back(SyntaxParserErrorCodes::UnknownParameterType);
                    }
                    break;
                    }
                }
                else
                {
                    m_syntaxErrors.push_back(SyntaxParserErrorCodes::EmptyParameter);
                    m_positionalParameters.push_back("");
                }
            }
        }

    public:
        inline auto numParameters() const noexcept
        {
            return m_positionalParameters.size() +
            m_switchParameters.size() +
            m_optionParameters.size();
        }

        inline bool hasParameters() const noexcept
        {
            return !(m_positionalParameters.empty() ||
                m_switchParameters.empty() ||
                m_optionParameters.empty());
        }

        inline auto numSyntaxErrors() const
        {
            return std::count_if(m_syntaxErrors.cbegin(),
                m_syntaxErrors.cend(),
                [](const auto error) {
                    return error != SyntaxParserErrorCodes::NoError;
                });
        }

        inline bool hasValidSyntax() const noexcept
        {
            return numSyntaxErrors() == 0;
        }
    private:
        std::vector<SyntaxParserErrorCodes> m_syntaxErrors;
        std::vector<PositionalParameter> m_positionalParameters;
        std::vector<SwitchParameter> m_switchParameters;
        std::vector<OptionParameter> m_optionParameters;

        friend ParametersParser create(int argc, char *argv[]);
        friend ParametersParser create(std::vector<std::string> commandLine);
    };

    ParametersParser create(std::vector<std::string> commandLine)
    {
        return ParametersParser(std::move(commandLine));
    }

    ParametersParser create(int argc, char *argv[])
    {
        std::vector<std::string> params(argc);
        for (int i=0;i<argc;++i)
        {
            params.emplace_back(argv[i]);
        }
        return create(std::move(params));
    }
}

#endif
