#include "../mtypes/include/str.hpp"
#include <sstream>
#include <string>

namespace lib
{
	str::str() {}
	str::str(inline_str source) : m_data(source.begin,source.end()) {}
	str::str(const std::string &source) : m_data(source.cbegin(),source.cend())	{}
	/* str::str(std::string &&source) : m_data(std::move(source.m_data)) {} */
	str::str(str &&source) : m_data{ source.m_data } {}

	str::str(const unsigned int n) : str{ std::to_string(n) } {}
	str::str(const signed int n) : str{ std::to_string(n) } {}
	str::str(const char c) : str{ 1, c } {}
	str::str(const str & n) : str{ n } {}
	str::str(const char * n) : str{ n } {}
	str::str(const float n) : str{ std::to_string(n) } {}
	str::str(const double n) : str{ std::to_string(n) } {}

	vector<str> str::split(const char separator) const
	{
		vector<str> result;
		std::stringstream ss((*this).c_str());
		str tok;

		while (std::getline(ss, tok, separator)) {
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
