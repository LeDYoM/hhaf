#pragma once

#ifndef LIB_LFPROPERTIES_HPP__
#define LIB_LFPROPERTIES_HPP__

#include <map>
#include <fstream>
#include <functional>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <sstream>

namespace lib
{
	class FProperty;

	class PropertiesReader
	{
	public:
		PropertiesReader() = delete;
		PropertiesReader &operator=(const PropertiesReader &other) = delete;
		PropertiesReader(const PropertiesReader &other) = delete;
		PropertiesReader(const str &file);

		~PropertiesReader() {}

		sptr<FProperty> value(const str &) const;


	protected:
		using CMap = std::map<str, sptr<FProperty>>;
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

	class FProperty
	{
	public:
		constexpr FProperty() noexcept : m_data{} {}
		constexpr FProperty(str &&t) noexcept : m_data(std::move(t)) {}

		FProperty(const FProperty&) = delete;
		FProperty& operator=(const FProperty&) = delete;

		FProperty(FProperty&&) = default;
		FProperty& operator=(FProperty&&) = delete;

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
		bool set(T&& v) noexcept
		{
			std::ostringstream tmpstream;
			tmpstream << v;
			m_data = tmpstream.str();
			return tmpstream.fail();
		}

		const str &getstr() const noexcept { return m_data; }
		constexpr bool empty() const noexcept { return m_data.empty(); }
	private:
		str m_data;

	};
}

#endif
