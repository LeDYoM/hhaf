#include <logger/include/commiters/thread_commiter.hpp>

#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <atomic>

namespace logger
{
using Message = std::string;

struct InnerData
{
    std::mutex m_mutex;
    std::jthread m_thread;
    std::queue<Message> m_msg_queue;
    std::atomic<bool> m_exit;
    void (*m_commit_function)(const char* const log_stream);
};

namespace
{
InnerData* m_data{nullptr};
}

void ThreadCommiterImpl::init(void (*cmt_log)(const char* const log_stream))
{
    m_data                    = new InnerData;
    m_data->m_commit_function = cmt_log;
    m_data->m_exit            = false;
    m_data->m_thread          = std::jthread(thread_func);
}

void ThreadCommiterImpl::finish()
{
    {
        std::lock_guard lck{m_data->m_mutex};
        m_data->m_exit.store(true);
    }

    if (m_data->m_thread.joinable())
    {
        m_data->m_thread.join();
    }

    delete m_data;
    m_data = nullptr;
}

void ThreadCommiterImpl::thread_func()
{
    Message message;

    while (!m_data->m_exit.load())
    {
        bool commit{false};
        {
            std::lock_guard lck{m_data->m_mutex};
            if (!m_data->m_msg_queue.empty())
            {
                {
                    message = std::move(m_data->m_msg_queue.front());
                    m_data->m_msg_queue.pop();
                    commit = true;
                }
            }
        }

        if (!m_data->m_exit.load())
            [[likely]]
            {
                if (commit)
                {
                    m_data->m_commit_function(message.c_str());
                }
                else
                {
                    std::this_thread::yield();
                }
            }
    }
}

void ThreadCommiterImpl::commitlog(const char* const log_stream)
{
    std::lock_guard lck{m_data->m_mutex};
    m_data->m_msg_queue.emplace(std::move(log_stream));
}

}  // namespace logger
