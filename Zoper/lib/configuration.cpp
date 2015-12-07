#include "configuration.hpp"
#include "log.hpp"

#include <vector>
#include <regex>

namespace lib
{
	Configuration::CDataMap Configuration::_data;

	Configuration::CMapLine split(const std::string& input, const std::string& regex) {
		// passing -1 as the sub match index parameter performs splitting
		std::sregex_token_iterator first(input.begin(), input.end(), std::regex(regex), -1),
			last;
		return Configuration::CMapLine(*first, *last);
	}

	Configuration::Configuration(const std::string file, bool overwrite /*= false*/)
		: _overwrite{overwrite}
	{
		CDataMap::iterator fIterator{ _data.find(file) };

		if (fIterator != _data.end())
		{
			// Configuration file already in use.
			currentMap = &(fIterator->second);
		}
		else
		{
			CMap cMap;

			std::ifstream f(file);

			if (f.is_open())
			{
				while (f)
				{
					std::string line;
					f >> line;
					CMapLine lineData(split(line, "="));
					cMap[lineData.first] = lineData.second;
				}
			}

			if (cMap.size() > 0)
			{
				_data[file] = cMap;
				currentMap = &(_data[file]);
			}
		}
	}

	s32 Configuration::getAsInt(const std::string &name) const
	{
		return std::stoi(getAsString(name));
	}

	std::string Configuration::getAsString(const std::string & name) const
	{
		CMap::iterator dataIterator = currentMap->find(name);
		if (dataIterator != currentMap->end())
		{
			return dataIterator->second;
		}
		LOG_ERROR("Key " << name << " not found in configuration");
		return std::string();
	}

	std::string Configuration::addConfigProperty(const std::string & name, const std::string & value)
	{
		if (_overwrite)
		{
			(*currentMap)[name] = value;
		}
		else
		{
			auto iterator = currentMap->find(name);
			if (iterator != currentMap->end())
			{
				return iterator->second;
			}
			else
			{
				currentMap->emplace(std::pair<std::string, std::string>(name, value));
			}
		}
		return value;
	}

	s32 Configuration::addConfigInt(const std::string & name, int value)
	{
		return std::stoi(addConfigProperty(name, std::to_string(value)));
	}
}
