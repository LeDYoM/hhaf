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
	template <typename T>
	class ConfigurationProperty
	{
	public:
		using type = T;
		using string = std::string;
		using stringstream = std::stringstream;
		ConfigurationProperty(stringstream &&t) : m_stream{ std::move(t) }, m_valid{ (m_stream >> m_data) } {}
		const type &operator()() const { return m_data; }
		type &operator()() { return m_data; }
		void set(const type &nv) { m_data = nv; }

		stringstream m_stream;
		type m_data;
		bool m_valid;
	};
	class Configuration
	{
	public:
		Configuration() = delete;
		Configuration &operator=(const Configuration &other) = delete;
		Configuration(const Configuration &other) = delete;
		Configuration(const std::string &file);

		~Configuration() {}

		template <typename T>
		ConfigurationProperty<T> value(const std::string &name) const { return ConfigurationProperty<T>(propertyStreamed(name)); }

		std::string addConfigProperty(const std::string &name, const std::string &value, bool overwrite = false);
		s32 addConfigInt(const std::string &name, int value, bool overwrite = false);

		bool join(const Configuration &other,const bool overwrite=true);
		using CMap = std::map<std::string, std::string>;
		using CMapLine = std::pair<std::string, std::string>;
		using CDataMap = std::map<std::string, CMap>;

	protected:

		std::stringstream propertyStreamed(const std::string &) const;
		bool configFileExists(const std::string &file);

		void for_each_property(std::function<void(const CMapLine&)> callback);
		bool saveConfig();
		std::vector<std::string> splitString(const std::string &input, const char separator);

	private:
		void loadFile(const std::string &file);
		const std::string currentFile;
		CMap *currentMap;
		static CDataMap _data;
	};
}

#endif
