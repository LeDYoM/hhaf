#include <hlog/include/cout_thread_commiter.hpp>

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <chrono>
#include <string>

namespace haf
{
using Message = std::string;

struct InnerData
{
    std::mutex mutex_;
    std::thread thread_;
    std::queue<Message> msg_queue_;
    bool exit;
};

namespace
{
    InnerData * data_{nullptr};
}


void COutThreadCommiter::init()
{
    data_          = new InnerData;
    data_->thread_ = std::thread(thread_func);
}

void COutThreadCommiter::finish()
{
    data_->exit = true;
    data_->thread_.join();
    delete data_;
}

void COutThreadCommiter::thread_func()
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
                message = data_->msg_queue_.front();
                std::lock_guard<std::mutex> lck{data_->mutex_};
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

void COutThreadCommiter::commitlog(const char* const log_stream)
{
    Message message{log_stream};
    std::lock_guard<std::mutex> lck{data_->mutex_};
    data_->msg_queue_.emplace(std::move(log_stream));
}

}  // namespace haf
