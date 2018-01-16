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

		using PositionalParameter = std::string;
		using SwitchParameter = PositionalParameter;
		using OptionParameter = std::pair<const std::string, const std::string>;

        enum class ParserErrorCodes
        {
            NoError,
            OptionWithoutEqual,
            EmptyOptionName,
            EmptyOptionValue,

			// Exceptional cases, might never be reached
			EmptyParameter,
			UnknownParameterType

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

        /// Method that given a parameter assumed as option,
        /// checks if it is well formed.
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
						return CheckOptionParameterReturnValue(ParserErrorCodes::EmptyOptionName, {});
                    }
                    if (value.empty())
                    {
						return CheckOptionParameterReturnValue(ParserErrorCodes::EmptyOptionValue, {});
                    }
					return CheckOptionParameterReturnValue(ParserErrorCodes::NoError, { std::move(name), std::move(value) });
                }
				return CheckOptionParameterReturnValue(ParserErrorCodes::EmptyOptionName, {});
            }
            // No '=' found
			return CheckOptionParameterReturnValue{ ParserErrorCodes::OptionWithoutEqual,{} };
        }

        inline ParametersParser(const int argc, const char *const argv[])
        {
            for (int i=1;i<argc;++i) {
                std::string param(argv[i]);

                if (!param.empty())
                {
					switch (getParameterType(param))
					{
					case ParameterType::Positional:
					{
						m_positionalParameters.push_back(std::move(param));
						m_parserErrors.push_back(ParserErrorCodes::NoError);
					}
					break;
					case ParameterType::Switch:
					{
						m_switchParameters.push_back(std::move(param));
						m_parserErrors.push_back(ParserErrorCodes::NoError);
					}
					break;
					case ParameterType::Option:
					{
						auto result(checkOptionParameter(param));
						m_parserErrors.push_back(std::get<0>(result));
						m_optionParameters.emplace_back(
							std::get<1>(result).first,
							std::get<1>(result).second);
					}
					break;

					default:
					{
						m_positionalParameters.push_back(std::move(param));
						m_parserErrors.push_back(ParserErrorCodes::UnknownParameterType);
					}
					break;
					}
                }
                else
                {
					m_parserErrors.push_back(ParserErrorCodes::EmptyParameter);
					m_positionalParameters.push_back("");
                }
            }
        }

    public:
        inline auto numParameters() const 
		{ 
			return m_positionalParameters.size() +
			m_switchParameters.size() +
			m_optionParameters.size(); 
		}

		inline bool hasParameters() const 
		{ 
			return !(m_positionalParameters.empty() ||
				m_switchParameters.empty() ||
				m_optionParameters.empty());
		}
    private:
		std::vector<ParserErrorCodes> m_parserErrors;
        std::vector<PositionalParameter> m_positionalParameters;
		std::vector<SwitchParameter> m_switchParameters;
		std::vector<OptionParameter> m_optionParameters;


		friend ParametersParser create(int argc, char *argv[]);
    };

    ParametersParser create(int argc, char *argv[])
    {
        return ParametersParser(argc, argv);
    }
}

#endif
