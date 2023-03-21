HTPS_PRAGMA_ONCE
#ifndef HAF_EVENTS_RECEIVER_INCLUDE_HPP
#define HAF_EVENTS_RECEIVER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/events/emitter.hpp>
#include <haf/include/events/connection.hpp>

namespace haf::evt
{
class ireceiver_t final
{
public:
    template <typename R, typename... Args>
    constexpr ireceiver_t& connect(emitter<Args...>& e, R r)
    {
        connections_.push_back(msptr<connection<Args...>>(e, core::move(r)));
        return *this;
    }

    template <typename T, typename R, typename... Args>
    constexpr ireceiver_t& connect(core::sptr<T> element,
                                   emitter<Args...>& emitter,
                                   R r)
    {
        connections_.push_back(msptr<shared_connection<T, Args...>>(
            core::move(element), emitter, core::move(r)));
        return *this;
    }

    template <typename T, typename R, typename... Args>
    constexpr ireceiver_t& shared_connect(core::sptr<T> element,
                                          emitter<Args...>& emitter,
                                          R r)
    {
        return connect(core::move(element), emitter, core::move(r));
    }

    template <typename... Args>
    constexpr ireceiver_t& connect(emitter<Args...>& e, emitter<Args...>& r)
    {
        connections_.push_back(msptr<connection<Args...>>(e, r));
        return *this;
    }

    template <typename... Args>
    constexpr ireceiver_t& connect(emitter<Args...>& e,
                                   core::function<void(Args...)> r)
    {
        connections_.push_back(
            core::msptr<connection<Args...>>(e, core::move(r)));
        return *this;
    }

    constexpr core::size_type size() const noexcept
    {
        return connections_.size();
    }

    constexpr bool empty() const noexcept { return connections_.empty(); }

private:
    core::vector<core::sptr<iconnection>> connections_;
};

using ireceiver = ireceiver_t;

}  // namespace haf::evt

#endif
