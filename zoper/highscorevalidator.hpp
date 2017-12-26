#pragma once

#ifndef ZOPER_HIGHSCORE_VALIDATOR_INCLUDE_HPP__
#define ZOPER_HIGHSCORE_VALIDATOR_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <lib/scene/components/texteditorcomponent.hpp>

namespace zoper
{
	class HighScoreValidator : public lib::scene::TextValidator
	{
	public:
		bool canAddChar(const char) override {
			return true;
		}

		bool isValidText(const lib::str&) override {
			return true;
		}
	};
}

#endif
