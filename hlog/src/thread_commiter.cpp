#include <hlog/include/thread_commiter.hpp>
#include <hlog/include/cout_commiter.hpp>
#include <hlog/include/file_commiter.hpp>

#include <mutex>
#include <thread>
#include <queue>
#include <chrono>
#include <string>
#include <atomic>
#include <functional>
#include <logger/include/stream_commiter.hpp>
#include <logger/include/mixin_commiter.hpp>

namespace logger
{
using Message = std::string;

struct InnerData
{
    std::mutex mutex_;
    std::thread thread_;
    std::queue<Message> msg_queue_;
    std::atomic<bool> exit;
    std::byte _padding[3];
    std::function<void(const char* const log_stream)> commit_function;
    InnerData()                 = default;
    InnerData(InnerData const&) = delete;
    InnerData& operator=(InnerData const&) = delete;
    InnerData(InnerData&&)                 = default;
    InnerData& operator=(InnerData&&) = default;
};

namespace
{
InnerData* data_{nullptr};
using Commiter = logger::MixinCommiter<COutCommiter, FileCommiter>;

}  // namespace

void ThreadCommiterImpl::init(void (*cmt_log)(const char* const log_stream))
{
    data_                  = new InnerData;
    data_->commit_function = cmt_log;
    data_->exit            = false;
    data_->thread_         = std::thread(thread_func);
}

void ThreadCommiterImpl::finish()
{
    data_->exit.store(true);
    auto& thread{data_->thread_};

    if (thread.joinable())
    {
        thread.join();
    }
    delete data_;
}

void ThreadCommiterImpl::thread_func()
{
    Message message;

    while (!data_->exit.load())
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
            char const* const msg{message.c_str()};
            Commiter::commitlog(msg);
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

void ThreadCommiterImpl::commitlog(const char* const log_stream)
{
    Message message{log_stream};
    std::lock_guard<std::mutex> lck{data_->mutex_};
    data_->msg_queue_.emplace(std::move(log_stream));
}

}  // namespace logger
