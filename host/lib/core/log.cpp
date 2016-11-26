#include "log.hpp"
#include "compileconfig.hpp"
#include "exceptions.hpp"

#ifdef __USE_LOGS__

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

void print_impl()
{
	log_stream() << '\n';
}

void commitLog()
{
	auto outstr(log_output_stream.str());
#ifdef __LOGFILE__
	if (logFile.is_open())
		logFile << outstr;
#endif
	std::cout << outstr;
#if defined(_MSC_VER) || defined(__BORLANDC__)
	OutputDebugString(outstr.c_str());
#endif
	log_output_stream.clear();
}

#ifdef __MULTITHREAD_LOG__
	#include <queue>
	#include <string>
	#include <thread>
	#include <mutex>
	#include <condition_variable>

	std::queue<LogMessage> logQueue;
	std::mutex _mutex;
	std::condition_variable _condVar;

	void doLogOutput();
	bool doLoop = true;

	void logOutput(const LogType lt, const std::string&str)
	{
		std::unique_lock<std::mutex> _lock(_mutex);
		logQueue.push({ lt, str });
		_condVar.notify_all();
	}

	void doLogOutput()
	{
		while (doLoop) {
			{
				std::unique_lock<std::mutex> _lock(_mutex);
				if (logQueue.empty())
				{
					_condVar.wait(_lock);
				}
				else
				{
					while (!logQueue.empty())
					{
						const auto&&str (logQueue.front());
						commitLog(str);
						logQueue.pop();
					}
				}
			}
		}
	}

	std::thread t1(doLogOutput);
#else
void logOutput()
{
	commitLog();
}
#endif

void finishLog()
{
#ifdef __MULTITHREAD_LOG__
	doLoop = false;
	_condVar.notify_all();
	t1.join();
#endif
#ifdef __LOGFILE__
	logFile.close();
#endif
}

std::ostream & log_stream()
{
	return std::cout;
}

#else
void initLog() {}
void finishLog() {}

#endif
