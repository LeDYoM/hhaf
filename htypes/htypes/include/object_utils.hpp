#ifndef MTPS_HTYPES_OBJECT_UTILS_INCLUDE_HPP
#define MTPS_HTYPES_OBJECT_UTILS_INCLUDE_HPP

//#define LOG_MODE

#include "types.hpp"
#include "str.hpp"
#include "object.hpp"

namespace htps
{
    enum class TokenType : u8
    {
        Str,
        OpenObject,
        CloseObject,
        OpenArray,
        CloseArray,
        ObjectSeparator,
        KeyValueSeparator,
        Integer,
        Float
    };

    enum ErrorType : u8
    {
        NoError = 0U,
        InvalidCharacter,
        UnterminatedString,
        ExpectedTokenType
    };

    struct TokenPosition
    {
        size_type line;
        size_type column;
    };

    struct Token
    {
        str value;
        TokenType token_type{ TokenType::Str };
        TokenPosition position;
    };

    struct Error
    {
        Token token;
        ErrorType type{ ErrorType::NoError };
        u8 error_data;
    };

    class ErrorContainer
    {
    public:
        constexpr bool empty() const noexcept
        {
            return errors_.empty();
        }

        void merge(const ErrorContainer& other)
        {
            errors_ += other.errors_;
        }

        void error(const TokenType expected, const Token& found)
        {
            Error error_;
            error_.token = found;
            error_.type = ErrorType::ExpectedTokenType;
            error_.error_data = static_cast<u8>(expected);

            errors_.push_back(std::move(error_));
        }

        void unterminatedString(const Token& token)
        {
            Error error_;
            error_.token = token;
            error_.type = ErrorType::UnterminatedString;
            error_.error_data = 0U;

            errors_.push_back(std::move(error_));
        }

        void invalidCharacter(const Token& token, const str::char_type ch)
        {
            Error error_;
            error_.token = token;
            error_.type = ErrorType::InvalidCharacter;
            error_.error_data = static_cast<decltype(Error::error_data)>(ch);

            errors_.emplace_back(std::move(error_));
        }

        const vector<Error>& errors() const noexcept
        {
            return errors_;
        }
    
    private:
        vector<Error> errors_;
    };

    class Tokenizer
    {
    public:
        constexpr Tokenizer(str::const_iterator begin, 
            str::const_iterator end, 
            ErrorContainer &error_container) noexcept
            : begin_{ begin }, end_{ end }, errors_{ error_container } { }

        constexpr bool eof() const noexcept
        {
            return begin_ == end_;
        }

        constexpr bool isSpecial(str::const_iterator it)
        {
            return special_chars.cfind(*it) != special_chars.cend();
        }

        constexpr void advancePositionAndIterator()
        {
            if (*begin_ == '\n')
            {
                ++(position_.line);
                position_.column = 0U;
            }
            else
            {
                ++(position_.column);
            }
            ++begin_;
        }

        Token requestToken()
        {
            Token preparedToken{};
            bool next{ true };
            bool inDoubleBranckets{ false };

            while (begin_ != end_ && next)
            {
                if ((!std::isblank(*begin_) && !std::isspace(*begin_)) || inDoubleBranckets)
                {
                    if (*begin_ == '\"')
                    {
                        inDoubleBranckets = !inDoubleBranckets;
                        if (!inDoubleBranckets)
                        {
                            next = false;
                        }
                    }
                    else
                    {
                        // If it is the first char is not a blank,
                        // store the position.
                        if (preparedToken.value.empty())
                        {
                            preparedToken.position = position_;
                        }

                        // If we found a special character and we are not
                        // in double brackets mode.
                        if (isSpecial(begin_) && !inDoubleBranckets)
                        {
                            // If it is special, but the first char in the
                            // token, store it.
                            if (preparedToken.value.empty())
                            {
                                preparedToken.value.push_back(*begin_);
                            }
                            else
                            {
                                // If it is special, but not the first one,
                                // it has to be the first one of the next token,
                                // so put it back for processing.
                                // Note: No danger in underflowing the iterator,
                                // because if it where the first one,
                                // preparedToken will not be empty.
                                --begin_;
                            }
                            next = false;
                        }
                        else
                        {
                            // If it is not special char, store it
                            // in the current token.
                            preparedToken.value.push_back(*begin_);
                        }
                    }
                }
                else if (!preparedToken.value.empty())
                {
                    // If we found a blank char and there is a pending token,
                    // stop the loop and return it.
                    next = false;
                }
                advancePositionAndIterator();
            }

            if (next)
            {
                if (!preparedToken.value.empty())
                {
                    errors_.unterminatedString(preparedToken);
                }
            }

            return preparedToken;
        }

        Token nextToken()
        {
            Token next{ requestToken() };

            // Check for reserved values.
            if (next.value.size() == 1U)
            {
                // Small optimization, you do not need to enter the switch
                // if it is not one of the special characters.
                if (isSpecial(next.value.cbegin()))
                {
                    switch (next.value[0U])
                    {
                    case '{':
                        next.token_type = TokenType::OpenObject;
                        break;
                    case '}':
                        next.token_type = TokenType::CloseObject;
                        break;
                    case '[':
                        next.token_type = TokenType::OpenArray;
                        break;
                    case ']':
                        next.token_type = TokenType::CloseArray;
                        break;
                    case ',':
                        next.token_type = TokenType::ObjectSeparator;
                        break;
                    case ':':
                        next.token_type = TokenType::KeyValueSeparator;
                        break;
                    }
                }
            }

            if (next.value.is<s32>())
            {
                return { next.value, TokenType::Integer, {}};
            }
            else if (next.value.is<f32>())
            {
                return { next.value, TokenType::Float, {} };
            }
            return { next.value, next.token_type, {} };
        }

    private:

        str::const_iterator begin_;
        str::const_iterator end_;
        TokenPosition position_{};
        vector<str::char_type> special_chars{ '{', '}', ',', ':', '[', ']' };
        ErrorContainer& errors_;
    };

    class Scaner
    {
    public:
        constexpr Scaner(const str& input)
            : tokenizer_{ input.cbegin(), input.cend(), error_container_ } { }

        const vector<Token> scan()
        {
            while (!tokenizer_.eof() && error_container_.empty())
            {
                Token t{ tokenizer_.nextToken() };
#ifdef LOG_MODE
                LOG("Token found: " << int(t.token_type) << "\t: " << t.value.c_str());
#endif
                tokens_.push_back(std::move(t));
            }

            LOG("Scanner completed---------------------------------------");

            return tokens_;
        }

        constexpr const ErrorContainer& errors() const noexcept { return error_container_; }

    private:
        Tokenizer tokenizer_;
        vector<Token> tokens_;
        ErrorContainer error_container_;
    };

    // Parser	------------------------------------------------------------------------------------------------

    class InternalParserInterface
    {
    public:
        using TokenVector = vector<Token>;
        using TokenVectorCIterator = vector<Token>::const_iterator;

        InternalParserInterface(TokenVectorCIterator begin, const TokenVectorCIterator end)
            : tokens_begin_{ begin }, tokens_end_{ end } {}

        template <typename T>
        pair<Object, ErrorContainer> push_state()
        {
            T p(tokens_begin_, tokens_end_);
            InternalParserInterface& ref{ p };
            ref.parse();
            this->tokens_begin_ = ref.tokens_begin_;
            return { ref.innerObject(), ref.errors() };
        }

        template <typename T>
        void pushAndStore(const str& property_name)
        {
            auto[result_obj, next_state_errors] = push_state<T>();
            obj_.set(property_name, result_obj);
            errors_.merge(next_state_errors);
        }

        inline str readPropertyNameAndAdvance()
        {
            str property_name(getFromExpectedTypeAndAdvance(TokenType::Str));
            expectTypeAndAdvance(TokenType::KeyValueSeparator);
            return property_name;
        }

        bool pendingProperty() const
        {
            return currentTokenIsOfType<TokenType::Str>() || currentTokenIsOfType<TokenType::Integer>() || currentTokenIsOfType<TokenType::Float>();
        }

        bool storeIfPendingProperty(const str& property_name)
        {
            if (pendingProperty())
            {
                obj_.set(property_name, currentTokenAndAdvance().value);
                return true;
            }
            return false;
        }

        template <typename T, TokenType token_type_value>
        bool storeIfPendingThing(const str& property_name)
        {
            if (currentTokenIsOfType<token_type_value>())
            {
                pushAndStore<T>(property_name);
                return true;
            }
            return false;
        }

        constexpr bool pendingTokens() const noexcept
        {
            return tokens_begin_ != tokens_end_;
        }

        constexpr const Token& currentToken() const
        {
            return *tokens_begin_;
        }

        constexpr void advanceTokenVector() noexcept
        {
            if (tokens_begin_ != tokens_end_)
            {
                ++tokens_begin_;
            }
        }

        inline Token currentTokenAndAdvance()
        {
            const auto t{ currentToken() };
            advanceTokenVector();
            return t;
        }

        constexpr void expectType(const TokenType expectedCurrent)
        {
            const Token& current_token{ currentToken() };
            if (current_token.token_type != expectedCurrent)
            {
                errors_.error(expectedCurrent, current_token);
            }
        }

        constexpr const str& getFromExpectedType(const TokenType expectedCurrent)
        {
            expectType(expectedCurrent);
            return currentToken().value;
        }

        inline void expectTypeAndAdvance(const TokenType expectedCurrent)
        {
            const Token& current_token{ currentTokenAndAdvance() };
            if (current_token.token_type != expectedCurrent)
            {
                errors_.error(expectedCurrent, current_token);
            }
        }

        inline const str& getFromExpectedTypeAndAdvance(const TokenType expectedCurrent)
        {
            const str& v{ currentToken().value };
            expectTypeAndAdvance(expectedCurrent);
            return v;
        }

        template <TokenType expected>
        constexpr bool currentTokenIsOfType() const
        {
            return currentToken().token_type == expected;
        }

        constexpr bool currentTokenIsOfTypeAndAdvanceIfItIs(const TokenType expectedCurrent)
        {
            const bool value{ currentToken().token_type == expectedCurrent };

            if (value)
            {
                advanceTokenVector();
            }

            return value;
        }

        inline bool currentTokenIsOfTypeAndAdvance(const TokenType expectedCurrent)
        {
            const bool valid{ currentTokenAndAdvance().token_type == expectedCurrent };
            return valid;
        }

        constexpr const Object &innerObject() const noexcept
        {
            return obj_;
        }

        constexpr const ErrorContainer& errors() const noexcept
        {
            return errors_;
        }

        virtual void parse() = 0;

    protected:
        TokenVectorCIterator tokens_begin_;
        const TokenVectorCIterator tokens_end_;
        ErrorContainer errors_{};
        Object obj_{};
    };

    class ListParser;

    class ObjectParser : public InternalParserInterface
    {
    public:
        using InternalParserInterface::InternalParserInterface;

        bool storeIfPendingObject(const str& property_name)
        {
            return storeIfPendingThing<ObjectParser, TokenType::OpenObject>(property_name);
        }

        bool storeIfPendingList(const str& property_name)
        {
            return storeIfPendingThing<ListParser, TokenType::OpenArray>(property_name);
        }

        bool storePendingValueAndAdvance(const str& property_name)
        {
            if (!storeIfPendingProperty(property_name))
            {
                if (!storeIfPendingObject(property_name))
                {
                    if (!storeIfPendingList(property_name))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        void parse() override
        {
            expectTypeAndAdvance(TokenType::OpenObject);

            do
            {
                str property_name{ readPropertyNameAndAdvance() };

                if (!storePendingValueAndAdvance(property_name))
                {
                    // Error
                    errors_.error(TokenType::OpenObject, currentToken());
                }
            } while (currentTokenIsOfTypeAndAdvanceIfItIs(TokenType::ObjectSeparator));

            expectTypeAndAdvance(TokenType::CloseObject);
        }
    };

    class ListParser : public ObjectParser
    {
    public:
        using ObjectParser::ObjectParser;

        void parse() override
        {
            expectTypeAndAdvance(TokenType::OpenArray);

            size_t counter{ 0U };

            do
            {
                str property_name{ str(Object::arraySeparator) + str::to_str(counter) };
                if (!storePendingValueAndAdvance(property_name))
                {
                    // Error
                    errors_.error(TokenType::OpenObject, currentToken());
                }
                ++counter;
            } while (currentTokenIsOfTypeAndAdvanceIfItIs(TokenType::ObjectSeparator));

            expectTypeAndAdvance(TokenType::CloseArray);
        }
    };

    class Parser : public InternalParserInterface
    {
    public:
        Parser(vector<Token> tokens)
            : InternalParserInterface{ tokens.cbegin(), tokens.cend() },
            global_tokens_{ std::move(tokens) }
        { }

        void parse() override
        {
            auto[result_obj, next_state_errors] = push_state<ObjectParser>();
            obj_ = result_obj;
            errors_.merge(next_state_errors);
        }

    private:
        vector<Token> global_tokens_;
    };

    class ObjectCompiler
    {
    public:
        constexpr ObjectCompiler(const str& input) noexcept
            : input_{ input } {}

        constexpr ObjectCompiler(str&& input) noexcept
            : input_{ std::move(input) } {}

        bool compile()
        {
            Scaner scaner{ input_ };
            const auto tokens(scaner.scan());
            if (scaner.errors().empty())
            {
                Parser parser(Scaner{ input_ }.scan());
                parser.parse();
                if (parser.errors().empty())
                {
                    output_ = parser.innerObject();
                    return true;
                }
                else
                {
                    errors_ = parser.errors();
                    return false;
                }
            }
            else
            {
                errors_ = scaner.errors();
                return false;
            }
        }

        constexpr const Object& result() const noexcept
        {
            return output_;
        }

        constexpr const ErrorContainer& errors() const noexcept
        {
            return errors_;
        }

    private:
        ErrorContainer errors_;
        str input_;
        Object output_;
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    constexpr void manageSeparatorForObjectIn(str&sso, bool& is_first, bool& contains_array_only)
    {
        if (!is_first)
        {
            sso << ",";
        }
        else
        {
            contains_array_only = false;
            sso << "{";
            is_first = false;
        }
    }

    constexpr void manageSeparatorForObjectOut(str&sso, bool& is_first)
    {
        if (!is_first)
        {
            sso << "}";
        }
    }

    constexpr void manageSeparatorForList(str&sso, bool& is_first)
    {
        if (!is_first)
        {
            sso << ",";
        }
        else
        {
            is_first = false;
        }
    }

    struct PropertyWrapper
    {
        str value;
    };

    str& operator<<(str&sso, const Object::ValueDictionary::const_iterator it);
    str& operator<<(str&sso, const Object::ObjectDictionary::const_iterator it);
    str& operator<<(str&sso, const PropertyWrapper& property_wrapper);

    inline str& operator<<(str&sso, const Object& obj)
    {
        bool contains_array_only{true};
        bool is_first{true};

        // Elements with objects (that are not arrays).
        for (auto it(obj.begin_objects()); it !=obj.end_objects(); ++it)
        {
            if (!Object::isArrayElement(*it))
            {
                manageSeparatorForObjectIn(sso, is_first, contains_array_only);
                sso << it;
            }
        }

        // Elements with values (that are not arrays)
        for (auto it(obj.begin_values()); it !=obj.end_values(); ++it)
        {
            if (!Object::isArrayElement(*it))
            {
                manageSeparatorForObjectIn(sso, is_first, contains_array_only);
                sso << it;
            }
        }

        // Andd now, arrays.
        size_type i{0U};
        bool next{true};
        bool is_first_array_element{true};

        do
        {
            const auto value(obj[i]);
            if (value.isValid())
            {
                if ((i++) == 0U)
                {
                    sso << "[";
                }
                if (value.isObject())
                {
                    manageSeparatorForList(sso, is_first_array_element);
                    sso << value.getObject();
                }
                else
                {
                    manageSeparatorForList(sso, is_first_array_element);
                    sso << PropertyWrapper{value.getValue()};
                }
            }
            else
            {
                next = false;
                if (!is_first_array_element)
                {
                    sso << "]";
                }
            }

        } while (next);

        manageSeparatorForObjectOut(sso, is_first);
    
        return sso;
    }

    inline str& operator<<(str&sso, const PropertyWrapper& property_wrapper)
    {
        const bool add_double_quotes = (!(property_wrapper.value.is<s32>()) && !(property_wrapper.value.is<f32>()));

        if (add_double_quotes)
        {
            sso << "\"";
        }

        sso << property_wrapper.value;

        if (add_double_quotes)
        {
            sso << "\"";
        }

        return sso;
    }

    inline str& operator<<(str&sso, const Object::ValueDictionary::const_iterator it)
    {
        if (!Object::isArrayElement(*it))
        {
            sso << (*it).first << ":";
            sso << PropertyWrapper{(*it).second};
        }
        return sso;
    }

    inline str& operator<<(str&sso, const Object::ObjectDictionary::const_iterator it)
    {
        if (!Object::isArrayElement(*it))
        {
            sso << (*it).first << ":" << (*it).second;
        }
        return sso;
    }
}

#endif
