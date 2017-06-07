#include "../include/types/str.hpp"
#include <sstream>

namespace lib
{
	str::str(const unsigned int n) : std::string{ std::to_string(n) } {}
	str::str(const signed int n) : std::string{ std::to_string(n) } {}
	str::str(const char c) : std::string{ 1, c } {}
	str::str(const str & n) : std::string{ n } {}
	str::str(const char * n) : std::string{ n } {}
	str::str(const float n) : std::string{ std::to_string(n) } {}
	str::str(const double n) : std::string{ std::to_string(n) } {}

	std::vector<str> str::split(const char separator) const
	{
		std::vector<str> result;
		std::stringstream ss(*this);
		str tok;

		while (getline(ss, tok, separator)) {
			result.push_back(std::move(tok));
		}
		return result;
	}
	str & str::append(const unsigned int n)
	{
		*this += std::to_string(n);
		return *this;
	}
	str & str::append(const signed int n)
	{
		*this += std::to_string(n);
		return *this;
	}
	str & str::append(const char c)
	{
		this->push_back(c);
		return *this;
	}
	str & str::append(const str & n)
	{
		*this += n;
		return *this;
	}
	str & str::append(const char * n)
	{
		*this += n;
		return *this;
	}
	str & str::append(const float n)
	{
		*this += std::to_string(n);
		return *this;
	}
	str & str::append(const double n)
	{
		*this += std::to_string(n);
		return *this;
	}
}
