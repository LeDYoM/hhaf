#pragma once

#ifndef PARPAR_LIB_INCLUDE_HPP__
#define PARPAR_LIB_INCLUDE_HPP__

#include "types.hpp"
#include "str.hpp"
#include <utility>
#include <algorithm>

namespace lib::parpar
{
    class ParametersParser;
    using str_t = str;

    template <typename T>
    using vector_t = vector<T>;

    using ParameterName = str_t;
    using PositionalParameter = str_t;
    using SwitchParameter = str_t;
    using OptionParameter = std::pair<str_t,str_t>;

    using PositionalParameterVector = vector_t<PositionalParameter>;
    using SwitchParameterVector = vector_t<SwitchParameter>;
    using OptionParameterVector = vector_t<OptionParameter>;

    ParametersParser create(vector_t<str_t> commandLine);
    ParametersParser create(int argc, char *argv[]);

    /**
     * \class ParametersParser
     *
     * \brief Help to collect, read and check command line parameters
     *
     * This class in the main block of this library. The library is done as
     * a hobby and learning purposes. It does not have a lot of super
     * features, it trys to be compant and easy to be understood and user.
     * Of course, no warranty is provided.
     *
     * \note Attempts at zen rarely work.
     *
     * \author (last to touch it) $Author: bv $
     *
     * \version $Revision: 0.9 $
     */
    class ParametersParser final
    {
    public:
        /// Enum to describe the possible errors of the parser.
        /// Could be checked with the corresponding functions.
        enum class SyntaxParserErrorCodes
        {
            NoError,
            OptionWithoutEqual,
            EmptyOptionName,
            EmptyOptionValue,
            IncorrectPositionalPosition,
            OptionAlreadySet,

            // Exceptional cases, might never be reached
            EmptyParameter,
            UnknownParameterType
        };

    private:

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
        static ParameterType getParameterType(const ParameterName &param)
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
            = std::pair<SyntaxParserErrorCodes,std::pair<str_t,str_t>>;

        /// Method that given a parameter assumed as option,
        /// checks if it is well formed.
        /// @param param Parameter string to be checked.
        /// @return A tuple with an error code and two strings.
        /// If the error code is no error, the two strings are filled with
        /// name and value.
        static COptionResult checkOptionParameter(const ParameterName &param)
        {
            // Find '=' sign
            const auto equalSign(param.find_first_of('='));

            if (equalSign != std::string::npos)
            {
                const str_t name(param.substr(1,equalSign-1));
                const str_t value(param.substr(equalSign+1));

                if (name.empty())
                {
                    return COptionResult(SyntaxParserErrorCodes::EmptyOptionName, {});
                }
                if (value.empty())
                {
                    return COptionResult(SyntaxParserErrorCodes::EmptyOptionValue, {param.substr(1),{}});
                }
                return COptionResult(SyntaxParserErrorCodes::NoError,
                    { std::move(name), std::move(value) });
            }
            // No '=' found
            return COptionResult{ SyntaxParserErrorCodes::OptionWithoutEqual, {param.substr(1),{}} };
        }

        inline ParametersParser(vector_t<str_t> argv)
        {
            bool searchForPositional{true};

            for (decltype(argv.size()) i{1};i<argv.size();++i) {
                str_t param{std::move(argv[i])};

                if (!param.empty())
                {
                    switch (getParameterType(param))
                    {
                    case ParameterType::Positional:
                    {
                        m_positionalParameters.push_back(std::move(param));
                        m_syntaxErrors.push_back(
                            searchForPositional?
                                SyntaxParserErrorCodes::NoError :
                                SyntaxParserErrorCodes::IncorrectPositionalPosition
                            );
                    }
                    break;
                    case ParameterType::Switch:
                    {
                        searchForPositional = false;
                        m_switchParameters.push_back(param.substr(2));
                        m_syntaxErrors.push_back(SyntaxParserErrorCodes::NoError);
                    }
                    break;
                    case ParameterType::Option:
                    {
                        searchForPositional = false;
                        auto result(checkOptionParameter(param));

                        // Check for duplicates
                        m_syntaxErrors.push_back(
                                    optionExists(std::get<1>(result).first)?
                                    SyntaxParserErrorCodes::OptionAlreadySet:
                                    std::get<0>(result));

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
        /// Check if there is an error in a parameter selected by index.
        /// @param position The index of the parameter to check.
        /// @returns The enum value containing the error or SyntaxParserErrorCodes::NoError
        /// if the index of parameter is out of bounds.
        inline auto errorAtParameter(const std::size_t position) const noexcept
        {
            return position < m_syntaxErrors.size()?
                        m_syntaxErrors[position]:
                        SyntaxParserErrorCodes::NoError;
        }

        /// Retrieve the number of positional parameters.
        /// @returns The value.
        inline auto numPositionalParameters() const noexcept
        {
            return m_positionalParameters.size();
        }

        /// Retrieve the number of switch parameters.
        /// @returns The value.
        inline auto numSwitchParameters() const noexcept
        {
            return m_switchParameters.size();
        }

        /// Retrieve the number of option parameters.
        /// @returns The value.
        inline auto numOptionParameters() const noexcept
        {
            return m_optionParameters.size();
        }

        inline auto numParameters() const noexcept
        {
            return m_positionalParameters.size() +
            m_switchParameters.size() +
            m_optionParameters.size();
        }

        inline bool emptyParameters() const noexcept
        {
            return m_positionalParameters.empty() &&
                m_switchParameters.empty() &&
                m_optionParameters.empty();
        }

        inline bool hasParameters() const noexcept
        {
            return !(emptyParameters());
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

        inline str positionalParameterAt(const std::size_t position) const
        {
            return (position < m_positionalParameters.size()) ?
                m_positionalParameters[position] : "";
        }

        inline bool switchExists(const str &swPar) const
        {
            return std::find(
                m_switchParameters.cbegin(),
                m_switchParameters.cend(),
                SwitchParameter{swPar}) != m_switchParameters.cend();
        }

        inline bool optionExists(const str &opPar) const
        {
            return optionValue(opPar).first;
        }

        inline std::pair<bool,str> optionValue(const str_t &opPar) const
        {
            auto iterator(std::find_if(
                m_optionParameters.cbegin(),
                m_optionParameters.cend(),
                [opPar](const OptionParameter &node)
                {
                    return node.first == opPar;
                }));

                return iterator == m_optionParameters.cend()?
                    std::make_pair(false,""):
                    std::make_pair(true,iterator->second);
        }

        inline str_t optionValueOrDefault(const str_t &opPar,
                                                const str &def) const
        {
            auto ov(optionValue(opPar));
            return ov.first?ov.second:def;
        }

        inline const auto& getOptions() const noexcept
        {
            return m_optionParameters;
        }
    private:
        std::vector<SyntaxParserErrorCodes> m_syntaxErrors;
        PositionalParameterVector m_positionalParameters;
        SwitchParameterVector m_switchParameters;
        OptionParameterVector m_optionParameters;

        friend ParametersParser parpar::create(int argc, char *argv[]);
        friend ParametersParser parpar::create(vector_t<str_t> commandLine);
    };

    ParametersParser create(vector_t<str_t> commandLine)
    {
        return ParametersParser(std::move(commandLine));
    }

    ParametersParser create(int argc, char *argv[])
    {
        vector_t<str> params(argc);
        for (int i=0;i<argc;++i)
        {
            params.emplace_back(argv[i]);
        }
        return create(std::move(params));
    }
}

#endif
