#pragma once

#ifndef LIB_MTYPES_TRANSLATOR_INCLUDE_HPP
#define LIB_MTYPES_TRANSLATOR_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "streamin.hpp"
#include "dicty.hpp"
#include "stack.hpp"

namespace lib
{
	enum class TokenType
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

	struct Token
	{
		str value;
		TokenType token_type{ TokenType::Str };
	};

	class Scaner
	{
	public:
		constexpr Scaner(SerializationStreamIn& ssi)
			: ssi_{ ssi.separator(' ') } { }

		const vector<Token> scan()
		{
			while (!ssi_.eof() && !ssi_.hasError())
			{
				tokens_.push_back(nextToken());
			}
			return tokens_;
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

		Token nextToken()
		{
			str value;
			TokenType token_type{ TokenType::Str };

			ssi_ >> value;

			// Check for reserved chars.
			if (value.size() == 1U)
			{
				switch (value[0U])
				{
				case '{':
					token_type = TokenType::OpenObject;
					break;
				case '}':
					token_type = TokenType::CloseObject;
					break;
				case '[':
					token_type = TokenType::OpenArray;
					break;
				case ']':
					token_type = TokenType::CloseArray;
					break;
				case ',':
					token_type = TokenType::ObjectSeparator;
					break;
				case ':':
					token_type = TokenType::KeyValueSeparator;
					break;
				}
			}

			if (isInteger(value))
			{
				return { value, TokenType::Integer };
			}
			else if (isFloat(value))
			{
				return { value, TokenType::Float };
			}
			return { value, token_type };
		}

		SerializationStreamIn& ssi_;
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
		pair<dicty::Object,const VectorOfErrors> push_state()
		{
			T p(tokens_begin_, tokens_end_);
			InternalParserInterface& ref{ p };
			ref.parse();
			return { ref.innerObject(), errors() };
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

		constexpr void expectTypeAndAdvance(const TokenType expectedCurrent)
		{
			const TokenType current(currentToken().token_type);
			if (current != expectedCurrent)
			{
				error(expectedCurrent, current);
			}
			advanceTokenVector();
		}

		constexpr const str& getFromExpectedTypeAndAdvance(const TokenType expectedCurrent)
		{
			const str& v{ currentToken().value };
			expectTypeAndAdvance(expectedCurrent);
			return v;
		}

		constexpr bool currentTokenIsOfType(const TokenType expectedCurrent)
		{
			return currentToken().token_type == expectedCurrent;
		}

		constexpr bool currentTokenIsOfTypeAndAdvance(const TokenType expectedCurrent)
		{
			const bool valid{ currentToken().token_type == expectedCurrent };
			advanceTokenVector();
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

	class ObjectParser : public InternalParserInterface
	{
	public:
		using InternalParserInterface::InternalParserInterface;

		void parse() override
		{
			expectTypeAndAdvance(TokenType::OpenObject);

			do
			{
				str property_name(getFromExpectedTypeAndAdvance(TokenType::Str));
				expectTypeAndAdvance(TokenType::KeyValueSeparator);
				if (currentTokenIsOfType(TokenType::Str))
				{
					obj_.set(property_name, currentToken().value);
				}
				else if (currentTokenIsOfType(TokenType::OpenObject))
				{
					auto[next_state, next_state_errors] = push_state<ObjectParser>();
					obj_.set(property_name, next_state);
					errors_ += next_state_errors;
				}
				else
				{
					// Error
					error(TokenType::OpenObject, currentToken().token_type);
				}
			} while (currentTokenIsOfTypeAndAdvance(TokenType::ObjectSeparator));
			expectTypeAndAdvance(TokenType::CloseObject);
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
			parseObject();
		}

		void parseObject()
		{
			push_state<ObjectParser>();
		}

	private:
		vector<Token> global_tokens_;
	};
}

#endif
