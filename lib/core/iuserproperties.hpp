#pragma once

#ifndef LIB_IUSERPROPERTIES_INCLUDE_HPP__
#define LIB_IUSERPROPERTIES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include "configuration.hpp"

namespace lib
{
	class IUserProperties
	{
	public:
		IUserProperties(str fName) : m_fileName{ fName } {}
		virtual ~IUserProperties() {}
		virtual void setProperties(Configuration &config) = 0;
	private:
		str m_fileName;
	};

}

#endif
