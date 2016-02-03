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
			BaseException(const Severity severity, const std::string &errorMessage) : m_severity{ severity }, m_message{ errorMessage } {}
			virtual ~BaseException() {}
		protected:
			const Severity m_severity;
			const std::string m_message;
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
