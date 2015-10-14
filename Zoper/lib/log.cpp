#include "log.hpp"

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

#include <iostream>

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
					std::cout << str;
#if defined(_MSC_VER) || defined(__BORLANDC__)
					OutputDebugString(str.c_str());
#endif
					logQueue.pop();
				}
			}
		}
	}

	std::thread t1(doLogOutput);

	void finishLog()
	{
		doLoop = false;
		t1.join();
	}
#else
void logOutput(const char *str)
{
	std::cout << str;
#if defined(_MSC_VER) || defined(__BORLANDC__)
	OutputDebugString(str);
#endif
}
void finishLog()
{

}

#endif
