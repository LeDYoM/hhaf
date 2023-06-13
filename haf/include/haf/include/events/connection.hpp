HAF_PRAGMA_ONCE
#ifndef HAF_EVENTS_CONNECTION_INCLUDE_HPP
#define HAF_EVENTS_CONNECTION_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/events/emitter.hpp>

namespace haf::evt
{
class iconnection
{
public:
    virtual bool disconnect() = 0;
    virtual ~iconnection()    = default;
};

template <template <typename... G> typename function_type,
          typename em_type,
          typename... Args>
class connection_t final : public iconnection
{
public:
    using emitter_type = em_type;

    /**
     * @brief Constructor to create a connection to a function
     *
     * @param e Emitter source.
     * @param f Function to connect.
     */
    constexpr connection_t(emitter_type& e, function_type<void(Args...)> f) :
        emitter_{e}, function_{core::move(f)}
    {
        emitter_.connect(function_);
    }

    /**
     * @brief Constructor to forward the connection to another connection (of
     * the same signature). That is, when the original emitter e is called, it
     * will generate a call to the second emitter.
     *
     * @param e Emitter source.
     * @param r Emitter receiver.
     */
    constexpr connection_t(emitter_type& e, emitter_type& r) :
        emitter_{e}, function_{[&r](Args... args) {
            r(core::forward<Args>(args)...);
        }}
    {
        emitter_.connect(function_);
    }

    constexpr bool disconnect() override
    {
        return emitter_.disconnect(function_);
    }

    constexpr void release() noexcept { function_ = decltype(function_){}; }

    ~connection_t() override
    {
        if (function_)
        {
            (void)(emitter_.disconnect(function_));
        }
    }

private:
    emitter_type& emitter_;
    function_type<void(Args...)> function_{nullptr};
};

template <typename T,
          template <typename... G>
          typename function_type,
          typename em_type,
          typename... Args>
class shared_connection_t final : public iconnection
{
public:
    using emitter_type = em_type;
    using conn = connection_t<core::function, emitter<Args...>, Args...>;
    /**
     * @brief Constructor to create a connection to a function
     *
     * @param e Emitter source.
     * @param f Function to connect.
     */
    constexpr shared_connection_t(core::sptr<T> element,
                                  emitter_type& e,
                                  function_type<void(Args...)> f) :
        m_inner_connection{core::msptr<conn>(e, core::move(f))},
        m_element_weak_pointer{element}
    {}

    bool disconnect() override
    {
        if (auto element_pointer{m_element_weak_pointer.lock()};
            element_pointer != nullptr)
        {
            m_inner_connection->disconnect();
            return true;
        }
        else
        {
            m_inner_connection->release();
            return false;
        }
    }

    ~shared_connection_t() override { (void)(disconnect()); }

private:
    core::sptr<conn> m_inner_connection;
    core::wptr<T> m_element_weak_pointer;
};

template <typename... Args>
using connection = connection_t<core::function, emitter<Args...>, Args...>;

template <typename T, typename... Args>
using shared_connection =
    shared_connection_t<T, core::function, emitter<Args...>, Args...>;

}  // namespace haf::evt

#endif
