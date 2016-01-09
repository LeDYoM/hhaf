#include "configuration.hpp"
#include "log.hpp"

#include <regex>

namespace lib
{

	Configuration::CDataMap Configuration::_data;

	std::vector<std::string> split_helper(const std::string& input, const std::string& regex)
	{
		// passing -1 as the sub match index parameter performs splitting
		if (input.find(regex[0]) != std::string::npos)
		{
			std::regex re(regex);
			std::sregex_token_iterator first(input.begin(), input.end(), re, -1), last;
			return{ first,last };
		}
		return{ };
	}

	Configuration::CMapLine split(const std::string& input, const std::string& regex)
	{
		auto splitted = split_helper(input, regex);

		if (splitted.size() < 1)
		{
			return { "","" };
		}
		else if (splitted.size() < 2)
		{
			return{ splitted[0],"" };
		}
		else
		{
			return{ splitted[0],splitted[1] };
		}
	}

	std::vector<std::string> Configuration::splitString(const std::string &input, const char separator)
	{
		std::string rest{ input };
		std::vector<std::string> result;

		while (rest.find(separator) != std::string::npos)
		{
			auto tResult = split_helper(input, std::string{ separator });
			rest = tResult[1];
			result.push_back(tResult[0]);
		}

		result.push_back(rest);
		return result;
	}

	Configuration::Configuration(const std::string &file)
		: currentFile(file)
	{
		loadFile(file);
	}

	void Configuration::loadFile(const std::string &file)
	{
		CDataMap::iterator fIterator{ _data.find(currentFile) };

		if (fIterator != _data.end())
		{
			// Configuration file already in use.
			LOG_DEBUG("Map data for " << currentFile << " found. Using it");
			currentMap = &(fIterator->second);
		}
		else
		{
			LOG_DEBUG("Map data for " << currentFile << " not created.");
			CMap cMap;

			if (file[0] != ':')
			{
				LOG_DEBUG("Trying to read file");
				std::ifstream f(currentFile);

				if (f.is_open())
				{
					while (f)
					{
						std::string line;
						f >> line;
						if (line.size() > 0)
						{
							CMapLine lineData(split(line, "="));
							cMap[lineData.first] = lineData.second;
							LOG_DEBUG("Adding key" << lineData.first << " with value " << lineData.second);
						}
					}
				}
				else
				{
					LOG_DEBUG("File " << file << " not found. Associating empty data to file");
				}
			}

			_data[file] = cMap;
			currentMap = &(_data[currentFile]);
		}
	}

	bool Configuration::configFileExists(const std::string &file)
	{
		std::ifstream f(file);
		return f.is_open();
	}

	void Configuration::for_each_property(std::function<void(const CMapLine&)> callback)
	{
		std::for_each(currentMap->begin(), currentMap->end(), callback);
	}

	s32 Configuration::getAsInt(const std::string &name, s32 defaultValue) const
	{
		const auto result = getAsString(name, "");
		if (result == "")
			return defaultValue;

		return std::stoi(result);
	}

	std::string Configuration::getAsString(const std::string & name, const std::string &defaultValue) const
	{
		CMap::iterator dataIterator = currentMap->find(name);
		if (dataIterator != currentMap->end())
		{
			return dataIterator->second;
		}
		return defaultValue;
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

	std::string Configuration::addConfigProperty(const std::string & name, const std::string & value, bool overwrite)
	{
		if (overwrite)
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

	s32 Configuration::addConfigInt(const std::string & name, int value, bool overwrite)
	{
		return std::stoi(addConfigProperty(name, std::to_string(value),overwrite));
	}

	bool Configuration::join(const Configuration &other, const bool overwrite)
	{
		if (currentFile != other.currentFile)
		{
			return false;
		}

		for (const auto &node : *(other.currentMap))
		{
			addConfigProperty(node.first, node.second, overwrite);
		}
		return true;
	}

	bool Configuration::saveConfig()
	{
		__ASSERT(currentFile.size() > 0, "Empty file name");
		__ASSERT(currentFile[0] != ':', "Cannot save memory streams");
		LOG_DEBUG("Saving configuration file " << currentFile);
		std::ofstream f(currentFile);

		if (f.is_open())
		{
			for_each_property([&f](const CMapLine &line)
			{
				f << line.first << "=" << line.second << std::endl;
				LOG_DEBUG("Written: " << line.first << "=" << line.second);
			});
			return true;
		}
		else
		{
			LOG_ERROR("Cannot write file " << currentFile);
			return false;
		}
	}

}
