#ifndef HTYPES_PARPAR_INCLUDE_HPP
#define HTYPES_PARPAR_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include <utility>
#include <algorithm>

namespace htps::parpar
{
using str_t = str;

template <typename T>
using vector_t = vector<T>;

// Forward declaration of main class.
class ParametersParser;

// Forward declare free functions to create parameters parser objects
ParametersParser create(vector_t<str_t> commandLine);
ParametersParser create(int argc, char* argv[]);

/**
 * @brief Help to collect, read and check command line parameters
 * This class provides a component to collect the command line parameters
 * and check them.
 */
class ParametersParser final
{
public:
    using ParameterName             = str_t;
    using PositionalParameter       = str_t;
    using SwitchParameter           = str_t;
    using OptionParameter           = pair<str_t, str_t>;
    using PositionalParameterVector = vector_t<PositionalParameter>;
    using SwitchParameterVector     = vector_t<SwitchParameter>;
    using OptionParameterVector     = vector_t<OptionParameter>;

    /**
     * @brief Enum to describe the possible errors of the parser.
     * Could be checked with the corresponding functions.
     */
    enum class SyntaxParserErrorCodes
    {
        /// There is no error
        NoError = 0U,
        /// Found an option without equal sign (starts with -, but no =)
        OptionWithoutEqual,
        /// Found an option without name (-=foo)
        EmptyOptionName,
        /// Found an option without value (-foo=)
        EmptyOptionValue,
        /// Found a positional argument in a wrong place
        IncorrectPositionalPosition,
        /// Found a duplicated optional argument
        OptionAlreadySet,

        // Exceptional cases, might never be reached
        /// There is an empty parameter
        EmptyParameter,
        /// Cannot determine the type of the parameter
        UnknownParameterType
    };

    /**
     * @brief Check if there is an error in a parameter selected by index.
     *
     * @param position The index of the parameter to check.
     * @return The enum value containing the error or
     * SyntaxParserErrorCodes::NoError if the index of parameter is out of
     * bounds.
     */
    SyntaxParserErrorCodes errorAtParameter(
        const std::size_t position) const noexcept
    {
        return position < syntax_errors_.size()
            ? syntax_errors_[position]
            : SyntaxParserErrorCodes::NoError;
    }

    /**
     * @brief Retrieve the number of positional parameters.
     * @return size_type The value.
     */
    size_type numPositionalParameters() const noexcept
    {
        return positional_parameters_.size();
    }

    /**
     * @brief Retrieve the number of switch parameters.
     * @return size_type The value.
     */
    size_type numSwitchParameters() const noexcept
    {
        return switch_parameters_.size();
    }

    /**
     * @brief Retrieve the number of option parameters.
     * @return size_type The value.
     */
    size_type numOptionParameters() const noexcept
    {
        return option_parameters.size();
    }

    /**
     * @brief Get the total number of parameters of all types
     * @return size_type The value
     */
    size_type numParameters() const noexcept
    {
        return numPositionalParameters() + numSwitchParameters() +
            numOptionParameters();
    }

    /**
     * @brief Ask if there is any parsed parameter
     * @return true No parsed parameters
     * @return false There is at least one parsed parameter
     */
    bool emptyParameters() const noexcept
    {
        return positional_parameters_.empty() && switch_parameters_.empty() &&
            option_parameters.empty();
    }

    /**
     * @brief Opposite of the emptyParameters() function
     * @see emptyParameters
     * @return true There is at least one parsed parameter
     * @return false No parsed parameters
     */
    inline bool hasParameters() const noexcept { return !(emptyParameters()); }

    /**
     * @brief Get the total number of syntax errors detected
     * @return The value
     */
    inline size_type numSyntaxErrors() const
    {
        return std::count_if(syntax_errors_.cbegin(), syntax_errors_.cend(),
                             [](const auto error) {
                                 return error !=
                                     SyntaxParserErrorCodes::NoError;
                             });
    }

    /**
     * @brief Method to ask if the proccessed parameters are syntactically
     * correct
     * @return true They are correct
     * @return false At least one error was detected
     */
    bool hasValidSyntax() const noexcept { return numSyntaxErrors() == 0U; }

    /**
     * @brief Get the positional parameter at a given index
     * @param position Position to fetch
     * @return str Empty string if the index is higher than the number of
     * positional parameters found. The value otherwise
     */
    str positionalParameterAt(size_type const position) const noexcept
    {
        return (position < positional_parameters_.size())
            ? positional_parameters_[position]
            : "";
    }

    /**
     * @brief Ask if a given positional parameter exists.
     *
     * @param poPar Name of the positional parameter
     * @return true Found
     * @return false Not found
     */
    bool positionalParameterExists(str const& poPar) const
    {
        return std::find(positional_parameters_.cbegin(),
                         positional_parameters_.cend(),
                         PositionalParameter{poPar}) !=
            positional_parameters_.cend();
    }

    bool switchExists(const str& swPar) const
    {
        return std::find(switch_parameters_.cbegin(), switch_parameters_.cend(),
                         SwitchParameter{swPar}) != switch_parameters_.cend();
    }

    bool onlyValidSwitches(vector_t<str_t> const& validSwitches) const noexcept
    {
        for (const auto& swt : validSwitches)
        {
            if (!switchExists(swt))
            {
                return false;
            }
        }
        return true;
    }

    bool optionExists(const str& opPar) const
    {
        return optionValue(opPar).first;
    }

    /**
     * @brief Get the value of a given option
     *
     * @param opPar Name of the option
     * @return pair<bool, str> The first element of the pair says if the option
     * was found. The second the value. If the option was not found, the value
     * contained in the second is rmpty string.d
     */
    pair<bool, str> optionValue(const str_t& opPar) const
    {
        auto iterator(std::find_if(option_parameters.cbegin(),
                                   option_parameters.cend(),
                                   [opPar](const OptionParameter& node) {
                                       return node.first == opPar;
                                   }));

        return iterator == option_parameters.cend()
            ? std::make_pair(false, str(""))
            : std::make_pair(true, str(iterator->second));
    }

    str_t optionValueOrDefault(const str_t& opPar, const str& def) const
    {
        auto ov(optionValue(opPar));
        return ov.first ? ov.second : def;
    }

    const auto& getOptions() const noexcept { return option_parameters; }

    bool onlyValidOptions(vector_t<str_t> const& validOptions) const noexcept
    {
        for (const auto& op : validOptions)
        {
            if (!optionExists(op))
            {
                return false;
            }
        }
        return true;
    }

private:
    enum class ParameterType
    {
        Positional,
        Switch,
        Option
    };

    /**
     * @brief Get the Parameter Type object
     * @see ParameterType
     * @param param The string representation of the parameter
     * @return ParameterType The enum value of the parameter parameter.
     */
    static ParameterType getParameterType(const ParameterName& param)
    {
        if (param[0] == '-')
        {
            if (param[1] == '-')
            {
                return ParameterType::Switch;
            }
            return ParameterType::Option;
        }
        return ParameterType::Positional;
    }

    using COptionResult = pair<SyntaxParserErrorCodes, pair<str_t, str_t>>;

    /**
     * @brief Method that given a parameter assumed as option,
     * checks if it is well formed.
     * @param param Parameter string to be checked.
     * @return COptionResult A tuple with an error code and two strings.
     * If the error code is no error, the two strings are filled with
     * name and value.
     */
    static COptionResult checkOptionParameter(const ParameterName& param)
    {
        // Find '=' sign
        const auto equalSign(param.find('='));

        if (equalSign != str_t::npos)
        {
            const str_t name(param.substr(1, equalSign - 1));
            const str_t value(param.substr(equalSign + 1));

            if (name.empty())
            {
                return COptionResult(SyntaxParserErrorCodes::EmptyOptionName,
                                     {});
            }
            if (value.empty())
            {
                return COptionResult(SyntaxParserErrorCodes::EmptyOptionValue,
                                     {param.substr(1), {}});
            }
            return COptionResult(SyntaxParserErrorCodes::NoError,
                                 {std::move(name), std::move(value)});
        }
        // No '=' found
        return COptionResult{SyntaxParserErrorCodes::OptionWithoutEqual,
                             {param.substr(1), {}}};
    }

    ParametersParser(vector_t<str_t> argv)
    {
        bool searchForPositional{true};

        for (decltype(argv.size()) i{1}; i < argv.size(); ++i)
        {
            str_t param{std::move(argv[i])};

            if (!param.empty())
            {
                switch (getParameterType(param))
                {
                    case ParameterType::Positional:
                    {
                        positional_parameters_.push_back(std::move(param));
                        syntax_errors_.push_back(
                            searchForPositional
                                ? SyntaxParserErrorCodes::NoError
                                : SyntaxParserErrorCodes::
                                      IncorrectPositionalPosition);
                    }
                    break;
                    case ParameterType::Switch:
                    {
                        searchForPositional = false;
                        switch_parameters_.push_back(param.substr(2));
                        syntax_errors_.push_back(
                            SyntaxParserErrorCodes::NoError);
                    }
                    break;
                    case ParameterType::Option:
                    {
                        searchForPositional = false;
                        auto result(checkOptionParameter(param));

                        // Check for duplicates
                        syntax_errors_.push_back(
                            optionExists(std::get<1>(result).first)
                                ? SyntaxParserErrorCodes::OptionAlreadySet
                                : std::get<0>(result));

                        option_parameters.emplace_back(
                            std::get<1>(result).first,
                            std::get<1>(result).second);
                    }
                    break;

                    default:
                    {
                        positional_parameters_.push_back(std::move(param));
                        syntax_errors_.push_back(
                            SyntaxParserErrorCodes::UnknownParameterType);
                    }
                    break;
                }
            }
            else
            {
                syntax_errors_.push_back(
                    SyntaxParserErrorCodes::EmptyParameter);
                positional_parameters_.push_back("");
            }
        }
    }

    vector_t<SyntaxParserErrorCodes> syntax_errors_;
    PositionalParameterVector positional_parameters_;
    SwitchParameterVector switch_parameters_;
    OptionParameterVector option_parameters;

    friend ParametersParser parpar::create(int argc, char* argv[]);
    friend ParametersParser parpar::create(vector_t<str_t> commandLine);
};

inline ParametersParser create(vector_t<str_t> commandLine)
{
    return ParametersParser(std::move(commandLine));
}

inline ParametersParser create(int const argc, char const* const argv[])
{
    vector_t<str> params(argc);
    for (int i = 0; i < argc; ++i)
    {
        params.emplace_back(argv[i]);
    }
    return create(std::move(params));
}
}  // namespace htps::parpar

#endif
