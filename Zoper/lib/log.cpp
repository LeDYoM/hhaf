#include "log.hpp"
#include "compileconfig.hpp"

#ifdef __USE_LOGS__

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

void commitLog(const char *str)
{
#ifdef __LOGFILE__
	if (logFile.is_open())
		logFile << str;
#endif
	std::cout << str;
#if defined(_MSC_VER) || defined(__BORLANDC__)
	OutputDebugString(str);
#endif
}

#ifdef __MULTITHREAD_LOG__
	#include <queue>
	#include <string>
	#include <thread>
	#include <mutex>
	#include <condition_variable>


	std::queue<std::string> logQueue;
	std::mutex _mutex;
	std::condition_variable _condVar;

	void doLogOutput();
	bool doLoop = true;

	void logOutput(const char *str)
	{
		std::unique_lock<std::mutex> _lock(_mutex);
		logQueue.push(str);
		_condVar.notify_all();
	}

	void doLogOutput()
	{
		while (doLoop)
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
					const std::string &str = logQueue.front();
					commitLog(str.c_str());
					logQueue.pop();
				}
			}
		}
	}

	std::thread t1(doLogOutput);
#else
void logOutput(const char *str)
{
	commitLog(str);
}
#endif

void finishLog()
{
#ifdef __MULTITHREAD_LOG__
	doLoop = false;
	t1.join();
#endif
#ifdef __LOGFILE__
	logFile.close();
#endif
}

#else
void initLog() {}
void finishLog() {}

#endif
