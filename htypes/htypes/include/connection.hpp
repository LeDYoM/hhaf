#ifndef HTPS_CONNECTION_INCLUDE_HPP
#define HTPS_CONNECTION_INCLUDE_HPP

#include "function.hpp"
#include "vector.hpp"

namespace htps
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
     * Creates an emitter object without receivers.
     */
    constexpr emitter_t() = default;

    /**
     * @brief Create an emitter with one receiver attached
     */
    constexpr emitter_t(emitter_callback_t f) : receivers_{std::move(f)} {}
    constexpr emitter_t(emitter_t const&) = default;
    constexpr emitter_t& operator=(const emitter_t&) = default;
    constexpr emitter_t(emitter_t&&) noexcept        = default;
    constexpr emitter_t& operator=(emitter_t&&) noexcept = default;

    constexpr void operator()(Args... args)
    {
        if (!receivers_.empty())
        {
            for (auto& f : receivers_)
            {
                f(std::forward<Args>(args)...);
            }
        }
    }

    constexpr void connect(emitter_callback_t f) noexcept
    {
        receivers_.emplace_back(std::move(f));
    }

    constexpr emitter_t& operator+=(emitter_callback_t f) noexcept
    {
        connect(std::move(f));
        return *this;
    }

    constexpr bool disconnect(emitter_callback_t const& f) noexcept
    {
        auto const old_size{receivers_.size()};

        (void)(receivers_.erase_if(
            [&f](auto const& element) { return f.equals(element); }));

        return receivers_.size() < old_size;
    }

    constexpr emitter_t& operator-=(emitter_callback_t const& f) noexcept
    {
        (void)(disconnect(f));
        return *this;
    }

    constexpr auto size() const noexcept { return receivers_.size(); }
    constexpr bool empty() const noexcept { return receivers_.empty(); }

    constexpr void clear() noexcept { receivers_.clear(); }
private:
    vector_type<emitter_callback_t> receivers_;
};

template <typename... Args>
using emitter = emitter_t<vector, function, Args...>;

class iconnection
{
public:
    virtual bool disconnect() = 0;
    virtual ~iconnection() {}
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
        emitter_{e}, function_{std::move(f)}
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
            r(std::forward<Args>(args)...);
        }}
    {
        emitter_.connect(function_);
    }

    inline bool disconnect() override
    {
        return emitter_.disconnect(function_);
    }

    ~connection_t() { (void)(emitter_.disconnect(function_)); }

private:
    emitter_type& emitter_;
    function_type<void(Args...)> function_;
};

template <typename... Args>
using connection = connection_t<function, emitter<Args...>, Args...>;

class ireceiver_t
{
public:
    template <typename R, typename... Args>
    constexpr void connect(emitter<Args...>& e, R r)
    {
        connections_.push_back(msptr<connection<Args...>>(e, std::move(r)));
    }

    template <typename... Args>
    constexpr void connect(emitter<Args...>& e, emitter<Args...>& r)
    {
        connections_.push_back(msptr<connection<Args...>>(e, r));
    }

private:
    vector<sptr<iconnection>> connections_;
};

using ireceiver = ireceiver_t;

}  // namespace htps

#endif
