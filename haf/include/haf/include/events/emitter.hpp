HTPS_PRAGMA_ONCE
#ifndef HAF_EVENTS_EMITTER_INCLUDE_HPP
#define HAF_EVENTS_EMITTER_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::evt
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
    constexpr emitter_t() noexcept = default;

    /**
     * @brief Create an emitter with one receiver attached
     */
    constexpr emitter_t(emitter_callback_t f) : m_receivers{htps::move(f)} {}
    constexpr emitter_t(emitter_t const&) = default;
    constexpr emitter_t& operator=(const emitter_t&) = default;
    constexpr emitter_t(emitter_t&&) noexcept        = default;
    constexpr emitter_t& operator=(emitter_t&&) noexcept = default;

    constexpr void operator()(Args... args)
    {
        if (!m_receivers.empty())
        {
            for (auto& f : m_receivers)
            {
                f(htps::forward<Args>(args)...);
            }
        }
    }

    constexpr void connect(emitter_callback_t f) noexcept
    {
        m_receivers.emplace_back(htps::move(f));
    }

    constexpr emitter_t& operator+=(emitter_callback_t f) noexcept
    {
        connect(htps::move(f));
        return *this;
    }

    constexpr bool disconnect(emitter_callback_t const& f) noexcept
    {
        auto const old_size{m_receivers.size()};

        (void)(m_receivers.erase_if(
            [&f](auto const& element) { return f.equals(element); }));

        return m_receivers.size() < old_size;
    }

    constexpr emitter_t& operator-=(emitter_callback_t const& f) noexcept
    {
        (void)(disconnect(f));
        return *this;
    }

    constexpr auto size() const noexcept { return m_receivers.size(); }
    constexpr bool empty() const noexcept { return m_receivers.empty(); }

    constexpr void clear() noexcept { m_receivers.clear(); }

private:
    vector_type<emitter_callback_t> m_receivers;
};

template <typename... Args>
using emitter = emitter_t<core::vector, core::function, Args...>;

}  // namespace haf::evt

#endif
