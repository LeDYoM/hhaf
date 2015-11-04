#include "configuration.hpp"
#include "log.hpp"

#include <vector>
#include <regex>

namespace lib
{
	Configuration::CMap Configuration::_data;

	Configuration::CMapLine split(const std::string& input, const std::string& regex) {
		// passing -1 as the submatch index parameter performs splitting
		std::sregex_token_iterator first(input.begin(), input.end(), std::regex(regex), -1 ),
			last;
		return Configuration::CMapLine(*first, *last);
	}

	s32 Configuration::getAsInt(const std::string &name) const
	{
		return std::stoi(getAsString(name));
	}

	std::string Configuration::getAsString(const std::string & name) const
	{
		CMap::iterator dataIterator = _data.find(name);
		if (dataIterator != _data.end())
		{
			return dataIterator->second;
		}
		LOG_ERROR("Key " << name << " not found in configuration");
		return std::string();
	}

	bool Configuration::addConfigProperty(const std::string & name, const std::string & value)
	{
		_data[name] = value;
		return true;
	}

	bool Configuration::addConfigInt(const std::string & name, int value)
	{
		return addConfigProperty(name, std::to_string(value));
	}

	bool Configuration::addConfigFile(const std::string & fileName)
	{
		std::ifstream file(fileName);
		bool result{ false };

		while (file)
		{
			std::string line;
			file >> line;
			CMapLine lineData(split(line,"="));
			result &= addConfigProperty(lineData.first, lineData.second);
		}
		return result;
	}

}
