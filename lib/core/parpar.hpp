#pragma once

#ifndef PARPAR_LIB_INCLUDE_HPP__
#define PARPAR_LIB_INCLUDE_HPP__

#include <string>
#include <vector>

namespace parpar
{
    class ParametersParser
    {
    private:

		enum class ParserErrorCodes
		{

		};
		struct ParserError
		{

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
					return ParameterType::Option;
				}
				return ParameterType::Switch;
			}
			return ParameterType::Positional;
		}
		inline ParametersParser(int argc, char *argv[])
        {
			bool searchingForPositionalParameters{ false };
            for (auto i=1;i<argc;++i) {
				std::string param(argv[i]);

				if (!param.empty())
				{
					if (searchingForPositionalParameters)
					{
						ParameterType paramType{ getParameterType(param) };
						if (param[0] != '-')
						{
							m_PositionalParameters.emplace_back(std::move(param));
						}
						else
						{
							searchingForPositionalParameters = false;
						}
					}
				}
            }
        }

	public:
		constexpr auto numParameters() const { return m_PositionalParameters.size(); }
		constexpr bool hasParameters() const { return !m_PositionalParameters.empty(); }

		std::vector<std::string> m_PositionalParameters;

		friend ParametersParser create(int argc, char *argv[]);
    };

	ParametersParser create(int argc, char *argv[])
	{
		return ParametersParser(argc, argv);
	}
}

#endif
