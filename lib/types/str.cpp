#include "../include/types/str.hpp"
#include <sstream>

namespace lib
{
	std::vector<str> str::split(const char separator) const
	{
		std::vector<str> result;
		std::stringstream ss(*this);
		str tok;

		while (getline(ss, tok, separator)) {
			result.push_back(tok);
		}
		return result;
	}
}
