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

namespace logger
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

    static void init() 
    {
        data_ = new InnerData;
        data_->thread_ = std::thread(thread_func); 
    }

    static void finish()
    {
        data_->exit = true;
        data_->thread_.join();
        delete data_;
    }

    static void thread_func()
    {
        data_->exit = false;
        Message message;

        while (!data_->exit)
        {
            // We dont lock this call because the only thread is only
            // adding, not deleting elements.
            if (!data_->msg_queue_.empty())
            {
                {
                    std::lock_guard<std::mutex> lck{data_->mutex_};
                    message = data_->msg_queue_.front();
                    data_->msg_queue_.pop();
                }
                std::cout << message << std::endl;
            }
            else
            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(10ms);
            }
        }
    }

    static inline void commitlog(const char* const log_stream)
    {
        std::lock_guard<std::mutex> lck{data_->mutex_};
        data_->msg_queue_.emplace(log_stream);
    }
};

}  // namespace logger

#endif
