#include "configuration.hpp"
#include "log.hpp"

#include <vector>
#include <regex>

namespace lib
{
	Configuration::Configuration(const std::string &fName)
	{
		_fileName = fName;
	}


	Configuration::~Configuration()
	{
	}

	std::pair<std::string,std::string> split(const std::string& input, const std::string& regex) {
		// passing -1 as the submatch index parameter performs splitting
		std::sregex_token_iterator first(input.begin(), input.end(), std::regex(regex), -1 ),
			last;
		return Configuration::CMapLine(*first, *last);
	}

	s32 Configuration::getAsInt(const std::string & section, const std::string & subSection) const
	{
		return s32();
	}

	void Configuration::readAllConfig()
	{
		std::ifstream file(_fileName);

		while (file)
		{
			std::string line;
			file >> line;
			CMapLine lineData(split(line,"="));
			_data[lineData.first] = lineData.second;
		}
	}

}
