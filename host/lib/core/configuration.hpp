#ifndef __LIB_CONFIGURATION_HPP__
#define __LIB_CONFIGURATION_HPP__

#include <string>
#include <map>
#include <fstream>
#include <functional>
#include <vector>
#include <sstream>
#include <lib/include/types.hpp>

namespace lib
{
	class ConfigurationProperty;

	class Configuration
	{
	public:
		Configuration() = delete;
		Configuration &operator=(const Configuration &other) = delete;
		Configuration(const Configuration &other) = delete;
		Configuration(const std::string &file);

		~Configuration() {}

		sptr<ConfigurationProperty> value(const std::string &name) const;

		using CMap = std::map<std::string, sptr<ConfigurationProperty>>;
		using CMapRawLine = std::pair<std::string, std::string>;
		using CMapLine = std::pair<const CMap::key_type, sptr<ConfigurationProperty>>;
		using CDataMap = std::map<std::string, CMap>;

	protected:

		bool configFileExists(const std::string &file);

		void for_each_property(std::function<void(const CMapLine&)> callback);
		bool saveConfig();
		std::vector<std::string> splitString(const std::string &input, const char separator);

	private:
		void loadFile(const std::string &file);
		const std::string currentFile;
		CMap *currentMap;
		static CDataMap m_data;
	};

	class ConfigurationProperty
	{
	public:
		using string = std::string;
		using stringstream = std::stringstream;
		ConfigurationProperty(string &&t) noexcept : m_data(std::move(t)) {}

		template <typename T>
		const T get() const noexcept
		{
			stringstream tmpstream(m_data);
			T tmp;
			tmpstream >> tmp;
			return tmp;
		}

		template <typename T>
		bool set(T&& v) noexcept
		{
			stringstream tmpstream(m_data);
			tmpstream << v;
			return tmpstream.fail();
		}

		const string &str() const noexcept { return m_data; }

		string m_data;
	};

}

#endif
