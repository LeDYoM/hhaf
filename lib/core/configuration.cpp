#include "configuration.hpp"
#include "log.hpp"
#include <string>

#include <regex>

namespace lib
{

	using CMapRawLine = std::pair<std::string, std::string>;

	Configuration::CDataMap Configuration::m_data;

	std::vector<std::string> split_helper(const std::string& input, const std::string& regex)
	{
		using std::vector;
		using std::string;
		using std::stringstream;
		vector<string> result;
		stringstream ss(input); // Turn the string into a stream.
		string tok;

		while (getline(ss, tok, regex[0])) {
			result.push_back(tok);
		}
		return result;
	}

	CMapRawLine split(const std::string& input, const std::string& regex)
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

	std::vector<std::string> Configuration::splitString(const std::string &input, char separator)
	{
		using std::vector;
		using std::string;
		using std::stringstream;
		vector<string> result;
		stringstream ss(input); // Turn the string into a stream.
		string tok;

		while (getline(ss, tok, separator)) {
			result.push_back(tok);
		}
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
			logDebug("Map data for ", currentFile, " found. Using it");
			currentMap = &(fIterator->second);
		}
		else {
			logDebug("Map data for ", currentFile, " not created.");
			CMap cMap;

			if (file[0] != ':') {
				logDebug("Trying to read file");
				std::ifstream f(currentFile);

				if (f.is_open()) {
					while (f) {
						std::string line;
						f >> line;
						if (!line.empty()) {
							CMapRawLine lineData(split(line, "="));
							logDebug("Adding key", lineData.first, " with value ", lineData.second);
							cMap.emplace(lineData.first, msptr<ConfigurationProperty>(std::move(lineData.second)));
						}
					}
				}
				else {
					logDebug("File ", file , " not found. Associating empty data to file");
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
		if (it != currentMap->end()) {
			return it->second;
		}
		else {
			return (currentMap->emplace(name, msptr<ConfigurationProperty>())).first->second;
		}
	}

	bool Configuration::saveConfig()
	{
		__ASSERT(!currentFile.empty(), "Empty file name");
		__ASSERT(currentFile[0] != ':', "Cannot save memory streams");
		logDebug("Saving configuration file ", currentFile);
		std::ofstream f(currentFile);

		if (f.is_open())
		{
			for_each_property([&f](const CMapLine &line) {
				f << line.first << "=" << line.second->str() << std::endl;
				logDebug("Written: ", line.first, "=", line.second->str());
			});
			return true;
		}
		else {
			logError("Cannot write file ", currentFile);
			return false;
		}
	}

}
