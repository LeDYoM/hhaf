#ifndef MTPS_CONNECTION_INCLUDE_HPP
#define MTPS_CONNECTION_INCLUDE_HPP

#include "function.hpp"
#include "vector.hpp"

namespace mtps
{
/**
 * @brief Class to store a group of callbacks where data can be emitted
 * @tparam Args Template parameters with the type data to be emitted
 */
template <template <typename T> typename vector_type,
          template <typename... G>
          typename function_type,
          typename... Args>
class emitter_t final
{
public:
    /**
     * Type of the parameters to emit
     */
    using emitter_callback_t = function_type<void(Args...)>;

    /**
     * @brief Default constructor.
     * Creates an emitter object without receivers
     */
    constexpr emitter_t() = default;

    /**
     * @brief Create an emitter with one receiver attached
     */
    constexpr emitter_t(emitter_callback_t f) : m_receivers{std::move(f)} {}
    constexpr emitter_t(const emitter_t&) = default;
    constexpr emitter_t& operator=(const emitter_t&) = default;
    constexpr emitter_t(emitter_t&&) noexcept        = default;
    constexpr emitter_t& operator=(emitter_t&&) noexcept = default;

    constexpr void operator()(Args... args)
    {
        if (!m_receivers.empty())
        {
            for (auto& f : m_receivers)
            {
                f(std::forward<Args>(args)...);
            }
        }
    }

    constexpr void connect(emitter_callback_t f) noexcept
    {
        m_receivers.emplace_back(std::move(f));
    }

    constexpr emitter_t& operator+=(emitter_callback_t f) noexcept
    {
        connect(std::move(f));
        return *this;
    }

    constexpr bool disconnect(emitter_callback_t const& f) noexcept
    {
        auto const old_size = m_receivers.size();

        (void)(m_receivers.erase_if([&f](auto const& element)
        {
            return f.equals(element);
        }));

        return m_receivers.size() < old_size;
    }

    constexpr emitter_t& operator-=(emitter_callback_t const& f) noexcept
    {
        (void)(disconnect(f));
        return *this;
    }

    constexpr auto size() const noexcept { return m_receivers.size(); }
    constexpr bool empty() const noexcept { return m_receivers.empty(); }

private:
    vector_type<emitter_callback_t> m_receivers;
};

template <typename... Args>
using emitter = emitter_t<vector, function, Args...>;

class iconnection
{
public:
    virtual bool disconnect() = 0;
    virtual ~iconnection() {}
};

// template <typename... Args>
template <template <typename... G> typename function_type,
          typename em_type,
          typename... Args>
class connection_t final : public iconnection
{
public:
    using emitter_type = em_type;
    constexpr connection_t(emitter_type& e, function_type<void(Args...)> f) :
        m_emitter{e}, m_function{std::move(f)}
    {
        m_emitter.connect(m_function);
    }

    /// Constructor to forward the connection to another connection (of the same
    /// signature). That is, when the original emitter e is called, it will
    /// generate a call to the second emitter.
    constexpr connection_t(emitter_type& e, emitter_type& r) :
        m_emitter{e}, m_function{[&r](Args... args) {
            r(std::forward<Args>(args)...);
        }}
    {
        m_emitter.connect(m_function);
    }

    inline bool disconnect() override
    {
        return m_emitter.disconnect(m_function);
    }

    ~connection_t() { (void)(m_emitter.disconnect(m_function)); }

private:
    emitter_type& m_emitter;
    function_type<void(Args...)> m_function;
};

template <typename... Args>
using connection = connection_t<function, emitter<Args...>, Args...>;

class ireceiver_t
{
public:
    template <typename R, typename... Args>
    constexpr void connect(emitter<Args...>& e, R r)
    {
        m_connections.push_back(msptr<connection<Args...>>(e, std::move(r)));
    }

    template <typename... Args>
    constexpr void connect(emitter<Args...>& e, emitter<Args...>& r)
    {
        m_connections.push_back(msptr<connection<Args...>>(e, r));
    }

private:
    vector<sptr<iconnection>> m_connections;
};

using ireceiver = ireceiver_t;

}  // namespace mtps

#endif
