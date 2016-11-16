#include "configuration.hpp"
#include "log.hpp"

#include <regex>

namespace lib
{

	Configuration::CDataMap Configuration::m_data;

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

	Configuration::CMapRawLine split(const std::string& input, const std::string& regex)
	{
		const auto splitted = split_helper(input, regex);

		if (splitted.size() < 1) {
			return { "","" };
		}
		else if (splitted.size() < 2) {
			return{ splitted[0],"" };
		}
		else {
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
		CDataMap::iterator fIterator{ m_data.find(currentFile) };

		if (fIterator != m_data.end()) {
			// Configuration file already in use.
			LOG_DEBUG("Map data for " << currentFile << " found. Using it");
			currentMap = &(fIterator->second);
		}
		else {
			LOG_DEBUG("Map data for " << currentFile << " not created.");
			CMap cMap;

			if (file[0] != ':') {
				LOG_DEBUG("Trying to read file");
				std::ifstream f(currentFile);

				if (f.is_open()) {
					while (f) {
						std::string line;
						f >> line;
						if (!line.empty()) {
							CMapRawLine lineData(split(line, "="));
							LOG_DEBUG("Adding key" << lineData.first << " with value " << lineData.second);
							cMap.emplace(lineData.first, msptr<ConfigurationProperty>(std::move(lineData.second)));
						}
					}
				}
				else {
					LOG_DEBUG("File " << file << " not found. Associating empty data to file");
				}
			}

			m_data[file] = std::move(cMap);
			currentMap = &(m_data[currentFile]);
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

	sptr<ConfigurationProperty> Configuration::value(const std::string & name) const
	{
		const auto &it(currentMap->find(name));
		return it != currentMap->end() ? it->second : msptr<ConfigurationProperty>();
	}

	bool Configuration::saveConfig()
	{
		__ASSERT(currentFile.size() > 0, "Empty file name");
		__ASSERT(currentFile[0] != ':', "Cannot save memory streams");
		LOG_DEBUG("Saving configuration file " << currentFile);
		std::ofstream f(currentFile);

		if (f.is_open())
		{
			for_each_property([&f](const CMapLine &line) {
				f << line.first << "=" << line.second->str() << std::endl;
				LOG_DEBUG("Written: " << line.first << "=" << line.second->str());
			});
			return true;
		}
		else {
			LOG_ERROR("Cannot write file " << currentFile);
			return false;
		}
	}

}
