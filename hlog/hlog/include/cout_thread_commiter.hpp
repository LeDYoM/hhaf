#pragma once

#ifndef LOGGER_LOG_COUT_THREAD_COMMITER_INCLUDE_HPP
#define LOGGER_LOG_COUT_THREAD_COMMITER_INCLUDE_HPP

#include <hlog/include/hlogexport.hpp>

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <chrono>
#include <string>

namespace haf
{

struct COutThreadCommiter
{
    using Message = std::string;
    struct InnerData
    {
        std::mutex mutex_;
        std::thread thread_;
        std::queue<Message> msg_queue_;
        bool exit;
    };

    static inline HLOG_API InnerData * data_;

    static void init();

    static void finish();

    static void thread_func();

    static void commitlog(const char* const log_stream);
};

}  // namespace logger

#endif
