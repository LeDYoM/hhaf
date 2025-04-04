#include <logger/include/commiters/thread_commiter.hpp>

#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <atomic>
#include <condition_variable>
#include <stop_token>
#include <memory>

namespace logger
{
using Message = std::string;

struct InnerData
{
    std::mutex m_mutex;
    std::jthread m_thread;
    std::queue<Message> m_msg_queue;
    std::condition_variable m_condition_variable;
    std::stop_source m_stop_source;
    void (*m_commit_function)(const char* const log_stream);

    InnerData()
    {
        int a=0;
        (void)(a);
    }

    ~InnerData()
    {
        int a=0;
        (void)(a);
    }
};

namespace
{
std::unique_ptr<InnerData> m_data{nullptr};
}

void thread_func(std::stop_token stop_token);

void ThreadCommiterImpl::init(void (*cmt_log)(const char* const log_stream))
{
    m_data                    = std::make_unique<InnerData>();
    m_data->m_commit_function = cmt_log;
    m_data->m_thread =
        std::jthread(thread_func, m_data->m_stop_source.get_token());
}

void ThreadCommiterImpl::finish()
{
    m_data->m_stop_source.request_stop();
    m_data->m_condition_variable.notify_all();

    if (m_data->m_thread.joinable())
    {
        m_data->m_thread.join();
    }

    m_data.reset();
}

void thread_func(std::stop_token stop_token)
{
    Message message;

    while (!stop_token.stop_requested())
    {
        bool commit{false};
        {
            std::unique_lock lck{m_data->m_mutex};
            m_data->m_condition_variable.wait(lck, [stop_token] {
                return stop_token.stop_requested() ||
                    !m_data->m_msg_queue.empty();
            });

            if (!stop_token.stop_requested() && !m_data->m_msg_queue.empty())
                [[likely]]
                {
                    message = std::move(m_data->m_msg_queue.front());
                    m_data->m_msg_queue.pop();
                    commit = true;
                }
        }

        if (!stop_token.stop_requested())
            [[likely]]
            {
                if (commit)
                    [[likely]] { m_data->m_commit_function(message.c_str()); }
            }
    }
}

void ThreadCommiterImpl::commitlog(const char* const log_stream)
{
    {
        std::lock_guard lck{m_data->m_mutex};
        m_data->m_msg_queue.emplace(std::move(log_stream));
    }
    m_data->m_condition_variable.notify_one();
}

}  // namespace logger
