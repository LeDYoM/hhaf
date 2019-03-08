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
			return value.convert(temp);
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

			if (value.starts_with("\""))
			{
				// Special case for strings in "string" form.
				while (!value.ends_with("\""))
				{
					str extravalue;
					ssi_ >> extravalue;
					value += extravalue;
				}
			}

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
		InternalParserInterface(size_type& index, const vector<Token>& tokens,
			dicty::Object& obj, stack<uptr<InternalParserInterface>>& state_stack)
			: index_{ index }, tokens_{ tokens }, object_{ obj }, state_stack_{ state_stack } {}

		template <typename T>
		void push_state()
		{
			state_stack_.push_back(muptr<T>(index_, tokens_, object_, state_stack_));
		}

		virtual void parse() = 0;
	protected:
		size_type& index_;
		const vector<Token>& tokens_;
		dicty::Object& object_;
		stack<uptr<InternalParserInterface>>& state_stack_;
	};

	class ObjectParser : public InternalParserInterface
	{
	public:
		using InternalParserInterface::InternalParserInterface;

		void parse() override
		{
		}
	};

	class Parser : InternalParserInterface
	{
	public:
		Parser(vector<Token> tokens)
			: InternalParserInterface{ current_index_, tokens, global_object_, global_state_stack_ },
			global_tokens_{ std::move(tokens) }
		{ }

		void parseObject()
		{
			push_state<ObjectParser>();
			while (!tokens_.empty())
			{
				state_stack_.back()->parse();
			}
		}

		dicty::Object object() const
		{
			return object_;
		}
	private:
		vector<Token> global_tokens_;
		dicty::Object global_object_;
		size_type current_index_{ 0U };
		stack<uptr<InternalParserInterface>> global_state_stack_;
		vector<u32> errors_;
	};
}

#endif
