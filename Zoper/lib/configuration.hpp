#ifndef __LIB_CONFIGURATION_HPP__
#define __LIB_CONFIGURATION_HPP__

#include <string>
#include <map>
#include <fstream>
#include "types.hpp"

namespace lib
{
	class Configuration
	{
	public:
		Configuration(const std::string file, bool overwrite = false);
		virtual ~Configuration() {}

		s32 getAsInt(const std::string &name) const;
		std::string getAsString(const std::string &name) const;

		typedef std::map<std::string, std::string> CMap;
		typedef std::pair<std::string, std::string> CMapLine;
		typedef std::map<std::string, CMap> CDataMap;

		std::string addConfigProperty(const std::string &name, const std::string &value);
		s32 addConfigInt(const std::string &name, int value);

		inline bool overwrite() const { return _overwrite; }
		inline void setOverwrite(bool nv) { _overwrite = nv; }

	private:
		bool _overwrite;
		const std::string currentFile;
		CMap *currentMap;
		static CDataMap _data;
	};

}

#endif
