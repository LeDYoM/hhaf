#pragma once

#ifndef LIB_CONFIGURATION_HPP__
#define LIB_CONFIGURATION_HPP__

#include <map>
#include <fstream>
#include <functional>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <sstream>

namespace lib
{
	class ConfigurationProperty;

	class Configuration
	{
	public:
		Configuration() = delete;
		Configuration &operator=(const Configuration &other) = delete;
		Configuration(const Configuration &other) = delete;
		Configuration(const str &file);

		~Configuration() {}

		sptr<ConfigurationProperty> value(const str &) const;


	protected:
		using CMap = std::map<str, sptr<ConfigurationProperty>>;
		using CMapLine = CMap::value_type;
		using CDataMap = std::map<str, CMap>;

		bool configFileExists(const str &file);

		void for_each_property(std::function<void(const CMapLine&)> callback);
		bool saveConfig();

	private:
		void loadFile(const str &file);
		const str currentFile;
		CMap *currentMap;
		static CDataMap m_data;
	};

	class ConfigurationProperty
	{
	public:
		constexpr ConfigurationProperty() noexcept : m_data("") {}
		constexpr ConfigurationProperty(str &&t) noexcept : m_data(std::move(t)) {}

		ConfigurationProperty(const ConfigurationProperty&) = delete;
		ConfigurationProperty& operator=(const ConfigurationProperty&) = delete;

		ConfigurationProperty(ConfigurationProperty&&) = default;
		ConfigurationProperty& operator=(ConfigurationProperty&&) = delete;

		template <typename T>
		T get() const noexcept
		{
			T tmp;
			(str(m_data)) >> tmp;
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

		const str &getstr() const noexcept { return m_data; }
		bool empty() const noexcept { return m_data.empty(); }
	private:
		str m_data;

	};

}

#endif
