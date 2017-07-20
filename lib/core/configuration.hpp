#pragma once

#ifndef LIB_CONFIGURATION_HPP__
#define LIB_CONFIGURATION_HPP__

#include <map>
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

		sptr<ConfigurationProperty> value(const str &);

		sptr<ConfigurationProperty> _registerProperty(const str&id, const str&defValue);

		template <typename T>
		T registerProperty(const str&id, const T&defValue)
		{
			auto prop(_registerProperty(id, str(defValue)));
			return prop->get<T>();
		}

	protected:
		using CMap = std::map<str, sptr<ConfigurationProperty>>;
		using CMapLine = CMap::value_type;
		using CDataMap = std::map<str, CMap>;

		bool configFileExists(const str &file);

		void for_each_property(std::function<void(const CMapLine&)> callback);
		bool saveConfig();

	private:
		vector<ConfigurationProperty> m_properties;
		bool propertyExists(const str&id) const;
		void loadFile(const str &file);
		const str currentFile;
		CMap m_currentMap;
	};

	class ConfigurationProperty
	{
	public:
		constexpr ConfigurationProperty() noexcept : m_data{} {}
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

		template <>
		str get<str>() const noexcept
		{
			return m_data;
		}

		template <typename T>
		void set(const T &v) noexcept
		{
			m_data = str(v);
		}

		template <>
		void set<str>(const str &v) noexcept
		{
			m_data = v;
		}

		const str &getstr() const noexcept { return m_data; }
		bool empty() const noexcept { return m_data.empty(); }
	private:
		str m_data;

	};
}

#endif
