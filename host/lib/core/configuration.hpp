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

		sptr<ConfigurationProperty> value(const std::string &) const;


	protected:
		using CMap = std::map<std::string, sptr<ConfigurationProperty>>;
		using CMapLine = std::pair<const CMap::key_type, sptr<ConfigurationProperty>>;
		using CDataMap = std::map<std::string, CMap>;

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
		constexpr ConfigurationProperty() noexcept : m_data("") {}
		constexpr ConfigurationProperty(string &&t) noexcept : m_data(std::move(t)) {}

		ConfigurationProperty(const ConfigurationProperty&) = delete;
		ConfigurationProperty& operator=(const ConfigurationProperty&) = delete;

		ConfigurationProperty(ConfigurationProperty&&) = default;
		ConfigurationProperty& operator=(ConfigurationProperty&&) = delete;

		template <typename T>
		const T get() const noexcept
		{
			std::istringstream tmpstream(m_data);
			T tmp;
			tmpstream >> tmp;
			return tmp;
		}

		template <typename T>
		bool set(T&& v) noexcept
		{
			std::ostringstream tmpstream;
			tmpstream << v;
			m_data = tmpstream.str();
			return tmpstream.fail();
		}

		const std::string &str() const noexcept { return m_data; }
		bool empty() const noexcept { return m_data == ""; }
	private:
		std::string m_data;

	};

}

#endif
