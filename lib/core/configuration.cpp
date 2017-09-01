#include "configuration.hpp"
#include <mtypes/include/log.hpp>
#include "file.hpp"
#include <fstream>
#include <regex>

namespace lib
{

	using CMapRawLine = std::pair<str, str>;

	Configuration::Configuration(const str &file)
		: currentFile(file)
	{
		loadFile(file);
	}

	bool Configuration::propertyExists(const str & id) const
	{
		const auto it(m_currentMap.find(id));
		return it != m_currentMap.end();
	}

	void Configuration::loadFile(const str &file)
	{
		log_debug_info("Reading file: ", file);

		if (file[0] != ':') {
			log_debug_info("Trying to read file");
			FileInput f(file);
			if (f.exists()) {
				auto fLines(f.readAsText());

				for (auto&& line : fLines) {
					if (!line.empty()) {
						auto vsplited(str(line).split('='));
						CMapRawLine lineData(
							vsplited.empty() ? str{} : vsplited[0], 
							vsplited.size() < 2 ? str{}:vsplited[1]);
						log_debug_info("Adding key", lineData.first, " with value ", lineData.second);
						m_currentMap.emplace(lineData.first, msptr<ConfigurationProperty>(std::move(lineData.second)));
					}
				}
			}
			else {
				log_debug_info("File ", file , " not found. Associating empty data to file");
			}
		}
	}

	bool Configuration::configFileExists(const str &file)
	{
		std::ifstream f(file.c_str());
		return f.is_open();
	}

	void Configuration::for_each_property(function<void(const CMapLine&)> callback)
	{
		std::for_each(m_currentMap.begin(), m_currentMap.end(), callback);
	}

	sptr<ConfigurationProperty> Configuration::value(const str & name)
	{
		const auto it(m_currentMap.find(name));
		if (it != m_currentMap.end()) {
			return it->second;
		}
		else {
			return (m_currentMap.emplace(name, msptr<ConfigurationProperty>())).first->second;
		}
	}

	sptr<ConfigurationProperty> Configuration::_registerProperty(const str & id, const str & defValue)
	{
		if (propertyExists(id)) {
			return value(id);
		}
		else {
			auto newProperty(msptr<ConfigurationProperty>());
			newProperty->set(defValue);
			return newProperty;
		}
	}

	bool Configuration::saveConfig()
	{
		__ASSERT(!currentFile.empty(), "Empty file name");
		__ASSERT(currentFile[0] != ':', "Cannot save memory streams");
		log_debug_info("Saving configuration file ", currentFile);
		std::ofstream f(currentFile.c_str());

		if (f.is_open())
		{
			for_each_property([&f](const CMapLine &line) {
				f << line.first.c_str() << "=" << line.second->getstr().c_str() << std::endl;
				log_debug_info("Written: ", line.first, "=", line.second->getstr());
			});
			return true;
		}
		else {
			log_debug_error("Cannot write file ", currentFile);
			return false;
		}
	}

}
