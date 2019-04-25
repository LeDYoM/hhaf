#pragma once

#ifndef LIB_MTYPES_TRANSLATOR_INCLUDE_HPP
#define LIB_MTYPES_TRANSLATOR_INCLUDE_HPP

#define LOG_MODE

#include "types.hpp"
#include "str.hpp"
#include "dicty.hpp"
#include "streamin.hpp"
#include <cctype>

#ifdef LOG_MODE
	#include <iostream>
#endif

namespace lib
{
#ifdef LOG_MODE
	#define LOG(x)	std::cout << x << std::endl;
	#define LOG_TOKEN(t) LOG("Token: " << int(t.token_type) << "\t: " << t.value.c_str());
#else
	#define LOG(x)
	#define LOG_TOKEN(t)
#endif

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
		UnterminatedString
	};

	struct Position
	{
		size_type line;
		size_type column;
	};

	struct Token
	{
		str value;
		TokenType token_type{ TokenType::Str };
		Position position;
	};

	class Tokenizer
	{
	public:
		constexpr Tokenizer(str::const_iterator begin, str::const_iterator end) noexcept
			: begin_{ begin }, end_{ end } { }

		constexpr bool eof() const noexcept
		{
			return begin_ == end_;
		}

		constexpr bool hasError() const noexcept
		{
			return last_error_ != ErrorType::NoError;
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
						// If it is the first char containing not blanks,
						// store the position.
						if (preparedToken.value.empty())
						{
							preparedToken.position = position_;
						}

						if (isSpecial(begin_))
						{
							// If it is special, but the first char in the
							// token, store it.
							if (preparedToken.value.empty())
							{
								preparedToken.value.append_char(*begin_);
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
							preparedToken.value.append_char(*begin_);
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
					last_error_ = ErrorType::UnterminatedString;
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

			if (isInteger(next.value))
			{
				return { next.value, TokenType::Integer };
			}
			else if (isFloat(next.value))
			{
				return { next.value, TokenType::Float };
			}
			return { next.value, next.token_type };
		}

	private:

		bool isInteger(const str& value) const
		{
			s32 temp;
			return value.convert(temp) && str(temp) == value;
		}

		bool isFloat(const str& value) const
		{
			f32 temp;
			return value.convert(temp);
		}

		str::const_iterator begin_;
		str::const_iterator end_;
		Position position_{};
		vector<str::char_type> special_chars{ '{', '}', ',', ':', '[', ']' };
		ErrorType last_error_{ ErrorType::NoError };
	};

	class Scaner
	{
	public:
		constexpr Scaner(SerializationStreamIn& ssi)
			: tokenizer_{ ssi.getData().begin(), ssi.getData().end() } { }

		constexpr Scaner(const str& input)
			: tokenizer_{ input.cbegin(), input.cend() } { }

		const vector<Token> scan()
		{
			while (!tokenizer_.eof() && !tokenizer_.hasError())
			{
#ifdef LOG_MODE
				Token t{ tokenizer_.nextToken() };
				LOG("Token found: " << int(t.token_type) << "\t: " << t.value.c_str());
				tokens_.emplace_back(std::move(t));
#else
				tokens_.emplace_back(tokenizer_.nextToken());
#endif
			}

			LOG("Scanner completed---------------------------------------");

			return tokens_;
		}

	private:
		Tokenizer tokenizer_;
		vector<Token> tokens_;
	};

	// Parser	------------------------------------------------------------------------------------------------

	class InternalParserInterface
	{
	public:
		using TokenVector = vector<Token>;
		using TokenVectorCIterator = vector<Token>::const_iterator;
		using VectorOfErrors = vector<pair<TokenType, TokenType>>;

		InternalParserInterface(TokenVectorCIterator begin, const TokenVectorCIterator end)
			: tokens_begin_{ begin }, tokens_end_{ end } {}

		template <typename T>
		pair<dicty::Object, VectorOfErrors> push_state()
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
			errors_ += next_state_errors;
		}

		inline str readPropertyNameAndAdvance()
		{
			str property_name(getFromExpectedTypeAndAdvance(TokenType::Str));
			expectTypeAndAdvance(TokenType::KeyValueSeparator);
			return property_name;
		}

		bool pendingProperty() const
		{
			return currentTokenIsOfType(TokenType::Str) || currentTokenIsOfType(TokenType::Integer) || currentTokenIsOfType(TokenType::Float);
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
			if (currentTokenIsOfType(token_type_value))
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
#ifdef LOG_MODE
//			LOG("Current token: ");
#endif
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

		constexpr void error(const TokenType expected, const TokenType found)
		{
			errors_.emplace_back(expected, found);
		}

		constexpr void expectType(const TokenType expectedCurrent)
		{
			const TokenType current(currentToken().token_type);
			if (current != expectedCurrent)
			{
				error(expectedCurrent, current);
			}
		}

		constexpr const str& getFromExpectedType(const TokenType expectedCurrent)
		{
			expectType(expectedCurrent);
			return currentToken().value;
		}

		inline void expectTypeAndAdvance(const TokenType expectedCurrent)
		{
			const TokenType current(currentTokenAndAdvance().token_type);
			if (current != expectedCurrent)
			{
				error(expectedCurrent, current);
			}
		}

		inline const str& getFromExpectedTypeAndAdvance(const TokenType expectedCurrent)
		{
			const str& v{ currentToken().value };
			expectTypeAndAdvance(expectedCurrent);
			return v;
		}

		constexpr bool currentTokenIsOfType(const TokenType expectedCurrent) const
		{
			return currentToken().token_type == expectedCurrent;
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

		constexpr const dicty::Object &innerObject() const noexcept
		{
			return obj_;
		}

		constexpr const VectorOfErrors& errors() const noexcept
		{
			return errors_;
		}

		virtual void parse() = 0;

	protected:
		TokenVectorCIterator tokens_begin_;
		const TokenVectorCIterator tokens_end_;
		VectorOfErrors errors_{};
		dicty::Object obj_{};
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
					error(TokenType::OpenObject, currentToken().token_type);
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
				str property_name{ str(dicty::Object::arraySeparator) + str(counter) };
				if (!storePendingValueAndAdvance(property_name))
				{
					// Error
					error(TokenType::OpenObject, currentToken().token_type);
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
			errors_ += next_state_errors;
		}

	private:
		vector<Token> global_tokens_;
	};
}

#endif
