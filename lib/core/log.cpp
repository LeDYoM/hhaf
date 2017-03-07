#include "log.hpp"
#include "compileconfig.hpp"
#include "exceptions.hpp"

#ifdef __USE_LOGS__
#ifdef __MULTITHREAD_LOG__
	#include <thread>
	#include <mutex>
#endif

using log_output_stream_t = std::ostringstream;

log_output_stream_t log_output_stream;

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

#include <iostream>

#ifdef __LOGFILE__
	#include <fstream>
	std::ofstream logFile;
#endif

void initLog()
{
#ifdef __LOGFILE__
	logFile.open(__LOGFILE__);
#endif
}

void commitLog()
{
	auto outstr(log_output_stream.str());
	log_output_stream.str(std::string());
#ifdef __LOGFILE__
	if (logFile.is_open())
		logFile << outstr;
#endif

#ifdef USE_COUT_FOR_LOGS
	std::cout << outstr;
#endif

#ifdef USE_IDE_CONSOLE_FOR_LOGS
	#if defined(_MSC_VER) || defined(__BORLANDC__)
		OutputDebugString(outstr.c_str());
	#endif
#endif

	log_output_stream.clear();
}

void print_impl()
{
	log_stream() << '\n';
	commitLog();
}

void finishLog()
{
#ifdef __LOGFILE__
	logFile.close();
#endif
}

lib::write_stream & log_stream() noexcept
{
	return log_output_stream;
}

#else
void initLog() {}
void finishLog() {}

#endif
