#ifndef __LIB_EXCEPTIONS_HPP__
#define __LIB_EXCEPTIONS_HPP__

#include <string>
#include <exception>
#include <lib/include/types.hpp>

namespace lib
{
	namespace excp
	{
		enum class Severity
		{
			FinishApp,
			Continue
		};
		class BaseException : public std::exception
		{
		public:
			BaseException(const Severity severity, const std::string &errorMessage) 
				: std::exception(errorMessage.c_str()),	m_severity{ severity } {}
			virtual ~BaseException() {}
		protected:
			Severity m_severity;
		};

		class LogErrorException : public BaseException
		{
		public:
			LogErrorException(const std::string &errorMessage) : BaseException{ Severity::Continue, errorMessage } {}
			virtual ~LogErrorException() {}
		};
	}
#define LIB_THROW(severity,component,message) throw excp::BaseException(severity,component+": "+message);
}

#endif
