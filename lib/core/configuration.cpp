#include "configuration.hpp"
#include "log.hpp"

#include <regex>

namespace lib
{

	using CMapRawLine = std::pair<str, str>;

	Configuration::CDataMap Configuration::m_data;

	Configuration::Configuration(const str &file)
		: currentFile(file)
	{
		loadFile(file);
	}

	void Configuration::loadFile(const str &file)
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
				std::ifstream f(currentFile.c_str());

				if (f.is_open()) {
					while (f) {
						str line;
						f >> line;
						if (!line.empty()) {
							auto vsplited(line.split('='));
							CMapRawLine lineData(
								vsplited.empty() ? str{} : vsplited[0], 
								vsplited.size() < 2 ? str{}:vsplited[1]);
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

	bool Configuration::configFileExists(const str &file)
	{
		std::ifstream f(file.c_str());
		return f.is_open();
	}

	void Configuration::for_each_property(std::function<void(const CMapLine&)> callback)
	{
		std::for_each(currentMap->begin(), currentMap->end(), callback);
	}

	sptr<ConfigurationProperty> Configuration::value(const str & name) const
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
		std::ofstream f(currentFile.c_str());

		if (f.is_open())
		{
			for_each_property([&f](const CMapLine &line) {
				f << line.first.c_str() << "=" << line.second->getstr().c_str() << std::endl;
				logDebug("Written: ", line.first, "=", line.second->getstr());
			});
			return true;
		}
		else {
			logError("Cannot write file ", currentFile);
			return false;
		}
	}

}
