HTPS_PRAGMA_ONCE
#ifndef HTYPES_SHARED_PTR_INCLUDE_HPP
#define HTYPES_SHARED_PTR_INCLUDE_HPP

#include <htypes/include/basic_types.hpp>
#include <htypes/include/unique_ptr.hpp>
#include <htypes/include/memory/allocator.hpp>

namespace htps
{
namespace shptr_detail
{
class counter
{
public:
    constexpr counter() noexcept = default;

    counter(const counter&) = delete;
    counter& operator=(const counter&) = delete;

    constexpr void reset() noexcept { m_counter = 0U; }

    constexpr fast_u32 get() const noexcept { return m_counter; }
    constexpr fast_u32 get_weak() const noexcept { return m_weak_counter; }

    constexpr void increment() noexcept { ++m_counter; }
    constexpr void increment_weak() noexcept { ++m_weak_counter; }

    constexpr void decrement() noexcept { --m_counter; }
    constexpr void decrement_weak() noexcept { --m_weak_counter; }

    [[nodiscard]] bool decrement_destroy(void* ptr)
    {
        decrement();
        if (m_counter == 0U)
        {
            if (m_weak_counter == 0U)
            {
                destroy(ptr);
                return true;
            }
        }
        return false;
    }

    virtual ~counter() noexcept {}
    virtual void destroy(void*) const noexcept {}

private:
    fast_u32 m_counter{1U};
    fast_u32 m_weak_counter{0U};
};

template <typename T>
struct ManagedPointer final : public counter
{
    using counter::counter;

    void destroy(void* ptr) const noexcept override
    {
        AllocatorType<T>::delete_one(static_cast<T*>(ptr));
    }
};

}  // namespace shptr_detail

template <typename T>
class sptr final
{
public:
    constexpr sptr() noexcept : m_ptr{nullptr}, m_counter{nullptr} {}
    constexpr sptr(std::nullptr_t) noexcept : m_ptr{nullptr}, m_counter{nullptr}
    {}

    explicit constexpr sptr(T* ptr) : m_ptr{htps::move(ptr)}
    {
        if (m_ptr != nullptr)
        {
            auto tmp{
                AllocatorType<shptr_detail::ManagedPointer<T>>::make_one()};
            m_counter = tmp;
        }
    }

    constexpr sptr(sptr&& sp) noexcept :
        sptr{htps::move(sp.m_ptr), htps::move(sp.m_counter)}
    {
        sp.m_ptr     = nullptr;
        sp.m_counter = nullptr;
    }

    constexpr sptr(sptr const& sp) noexcept : sptr{sp.m_ptr, sp.m_counter}
    {
        if (m_counter != nullptr)
        {
            m_counter->increment();
        }
    }

    constexpr sptr(uptr<T>&& up) noexcept : sptr{up.release()} {}

    template <typename U>
    constexpr sptr(uptr<U>&& up) noexcept : sptr{up.release()}
    {}

    template <typename T2>
    constexpr sptr(sptr<T2> const& sp) noexcept :
        sptr{static_cast<T*>(sp.m_ptr), sp.m_counter}
    {
        if (m_counter != nullptr)
        {
            m_counter->increment();
        }
    }

    constexpr sptr& operator=(sptr&& sp) noexcept
    {
        auto tmp_ptr{htps::move(sp.m_ptr)};
        auto tmp_counter{htps::move(sp.m_counter)};
        sp.m_ptr     = htps::move(m_ptr);
        sp.m_counter = htps::move(m_counter);
        m_ptr        = htps::move(tmp_ptr);
        m_counter    = htps::move(tmp_counter);
        return *this;
    }

    constexpr sptr& operator=(sptr const& sp) noexcept
    {
        *this = sptr{sp.m_ptr, sp.m_counter};
        if (m_counter != nullptr)
        {
            m_counter->increment();
        }
        return *this;
    }

    constexpr sptr& operator=(T*&& ptr) noexcept
    {
        *this = sptr{htps::move(ptr)};
        return *this;
    }

    constexpr void swap(sptr& other) noexcept
    {
        sptr _other{htps::move(other)};
        other = htps::move(*this);
        *this = htps::move(_other);
    }

    [[nodiscard]] constexpr u32 use_count() const noexcept
    {
        return m_counter == nullptr ? 0U : static_cast<u32>(m_counter->get());
    }

    void reset() noexcept { *this = sptr{nullptr, nullptr}; }

    void reset(T* newValue) noexcept { *this = sptr{newValue}; }

    [[nodiscard]] constexpr T* get() const noexcept { return m_ptr; }
    [[nodiscard]] constexpr T& operator*() const noexcept { return *m_ptr; }
    [[nodiscard]] constexpr T* operator->() const noexcept { return m_ptr; }
    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return m_ptr == nullptr;
    }

    [[nodiscard]] constexpr operator bool() const noexcept
    {
        return m_counter != nullptr && m_counter->get() > 0U;
    }

    constexpr ~sptr() noexcept
    {
        if (m_counter != nullptr)
        {
            if constexpr (!std::is_const_v<T>)
            {
                if (m_counter->decrement_destroy(static_cast<void*>(m_ptr)))
                {
                    m_ptr = nullptr;
                    AllocatorType<shptr_detail::counter>::delete_one_from_base(
                        m_counter);
                    m_counter = nullptr;
                }
            }
            else
            {
                m_counter->decrement();
            }
        }
    }

private:
    constexpr sptr(T* sp, shptr_detail::counter* cnt) noexcept :
        m_ptr{htps::move(sp)}, m_counter{htps::move(cnt)}
    {}

    template <typename T2>
    friend class sptr;

    template <typename T2>
    friend class wptr;

    template <class T1, class T2>
    friend sptr<T1> dynamic_pointer_cast(sptr<T2> const& other) noexcept;

    template <class T1, class T2>
    friend sptr<T1> dynamic_pointer_cast(sptr<T2>&& other) noexcept;

    template <class T1, class T2>
    friend sptr<T1> static_pointer_cast(sptr<T2> const& other) noexcept;

    template <class T1, class T2>
    friend sptr<T1> static_pointer_cast(sptr<T2>&& other) noexcept;

    T* m_ptr{nullptr};
    shptr_detail::counter* m_counter{nullptr};
};

template <typename T>
sptr(sptr<T>) -> sptr<T>;

template <typename T>
[[nodiscard]] constexpr bool operator==(sptr<T> const& lhs,
                                        std::nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <typename T>
[[nodiscard]] constexpr bool operator==(sptr<T> const& lhs,
                                        sptr<T> const& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename T, typename Y = T>
[[nodiscard]] constexpr bool operator==(sptr<T> const& lhs, Y* rhs) noexcept
{
    return lhs.get() == rhs;
}

template <typename T, typename... Args>
[[nodiscard]] sptr<T> msptr(Args&&... args)
{
    auto t{AllocatorType<T>::allocate(1)};
    AllocatorType<T>::construct(t, htps::forward<Args>(args)...);
    return sptr<T>{htps::move(t)};
}

template <class T, class T2>
[[nodiscard]] sptr<T> dynamic_pointer_cast(sptr<T2> const& other) noexcept
{
    if (other.m_counter != nullptr)
    {
        const auto ptr{dynamic_cast<T*>(other.get())};

        if (ptr)
        {
            sptr<T> result{ptr, other.m_counter};
            result.m_counter->increment();
            return result;
        }
    }

    return {};
}

template <class T, class T2>
[[nodiscard]] sptr<T> dynamic_pointer_cast(sptr<T2>&& other) noexcept
{
    if (other.m_counter != nullptr)
    {
        const auto ptr{dynamic_cast<T*>(other.get())};

        if (ptr)
        {
            auto tmp_counter{other.m_counter};
            other.m_counter = nullptr;
            other.m_ptr     = nullptr;
            return sptr<T>{ptr, tmp_counter};
        }
    }

    return {};
}

template <class T, class T2>
[[nodiscard]] sptr<T> static_pointer_cast(sptr<T2> const& other) noexcept
{
    if (other.m_counter != nullptr)
    {
        auto ptr{static_cast<T*>(other.get())};

        if (ptr)
        {
            auto result{sptr<T>{htps::move(ptr), htps::move(other.m_counter)}};
            result.m_counter->increment();
            return result;
        }
    }

    return {};
}

template <class T, class T2>
[[nodiscard]] sptr<T> static_pointer_cast(sptr<T2>&& other) noexcept
{
    if (other.m_counter != nullptr)
    {
        auto ptr{static_cast<T*>(other.get())};

        if (ptr)
        {
            auto tmp_counter{other.m_counter};
            other.m_counter = nullptr;
            other.m_ptr     = nullptr;
            return sptr<T>{htps::move(ptr), htps::move(tmp_counter)};
        }
    }

    return {};
}

}  // namespace htps

#endif
