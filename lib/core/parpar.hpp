#pragma once

#ifndef PARPAR_LIB_INCLUDE_HPP__
#define PARPAR_LIB_INCLUDE_HPP__

#include <string>
#include <vector>

namespace parpar
{
    class Parameter
    {
    public:
        constexpr Parameter(std::string param) : m_rawParam{std::move(param)} {}

        constexpr bool empty() const { return m_rawParam.empty(); }

        inline std::string cleanName() const
        {
        }

    private:
        std::string m_rawParam;
    };

    class Parameters
    {
    public:
        constexpr void addParamter(const char*const param_str)
        {
            std::string param(param_str);
            //TODO: Parse
            m_parameters.push_back(std::move(param));
        }

        constexpr auto numParameters() const { return m_parameters.size(); }
        constexpr bool hasParameters() const { return !m_parameters.empty(); }

    private:
        std::vector<Parameter> m_parameters;
    };

    class ParametersParser
    {
    public:

        Parameters setParameters(int argc, char *argv[])
        {
            for (auto i=1;i<argc;++i) {
                m_parameters.addParamter(argv[i]);
            }
        }
    private:
        Parameters m_parameters;
    };
}

#endif
