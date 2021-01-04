#ifndef MTYPES_FUNCTION_INCLUDE_HPP
#define MTYPES_FUNCTION_INCLUDE_HPP

#include <cassert>
#include "types.hpp"

namespace mtps
{
template <typename>
class function;

template <typename ReturnValue, typename... Args>
class function<ReturnValue(Args...)> final
{
public:
    constexpr function() noexcept : m_callable{nullptr} {}
    constexpr function(std::nullptr_t) noexcept : m_callable{nullptr} {}

    constexpr operator bool() const noexcept { return m_callable != nullptr; }

    template <typename T, typename V>
    constexpr function(T* const t, V function) :
        m_callable{msptr<CallableMethodPointerT<T>>(t, function)}
    {}

    template <typename T>
    constexpr function(T t) : m_callable{msptr<CallableT<T>>(std::move(t))}
    {}

    constexpr ReturnValue operator()(Args&&... args) const
    {
        assert(m_callable);
        return m_callable->Invoke(std::forward<Args>(args)...);
    }

    constexpr bool operator==(const function& other) const noexcept
    {
        return m_callable == other.m_callable;
    }

    constexpr bool equals(function const& other) const noexcept
    {
        return m_callable->equals(*(other.m_callable));
    }

private:
    class ICallable
    {
    public:
        virtual ~ICallable() {}
        virtual ReturnValue Invoke(Args&&...)                = 0;
        virtual bool equals(ICallable const&) const noexcept = 0;
    };

    template <typename T>
    class CallableT final : public ICallable
    {
    public:
        template <typename Y>
        constexpr CallableT(Y&& t) noexcept : m_t{std::forward<Y>(t)}
        {}

        inline ReturnValue Invoke(Args&&... args) override
        {
            return m_t(std::forward<Args>(args)...);
        }

        inline bool equals(CallableT const& other) const noexcept
        {
            return &m_t == &other.m_t;
        }

        inline bool equals(ICallable const& other) const noexcept override
        {
            CallableT const* const tmp = dynamic_cast<CallableT const*>(&other);
            if (tmp == nullptr)
            {
                return false;
            }
            return equals(*tmp);
        }

    private:
        T m_t;
    };

    template <class T>
    class CallableMethodPointerT final : public ICallable
    {
    public:
        typedef ReturnValue (T::*HandlerFunctionPtr)(Args...);

        constexpr CallableMethodPointerT(T* const receiver,
                                         const HandlerFunctionPtr function) :
            obj{receiver}, function_{function}
        {}

        inline ReturnValue Invoke(Args&&... args) override
        {
            return (obj->*function_)(std::forward<Args>(args)...);
        }

        inline bool equals(CallableMethodPointerT const& other) const noexcept
        {
            return obj == other.obj && function_ == other.function_;
        }

        inline bool equals(ICallable const& other) const noexcept override
        {
            function::CallableMethodPointerT<T> const* const tmp =
                dynamic_cast<function::CallableMethodPointerT<T> const*>(
                    &other);
            if (tmp == nullptr)
            {
                return false;
            }
            return equals(*tmp);
        }

    private:
        T* const obj;
        const HandlerFunctionPtr function_;
    };

    sptr<ICallable> m_callable;
};

template<typename ReturnType, typename... Args>
constexpr auto make_function(ReturnType(*p)(Args...))
{
  return function<ReturnType(Args...)>(p);
}

template<typename ReturnType, typename T, typename... Args>
constexpr auto make_function(T *obj, ReturnType(T::*p)(Args...))
{
  return function<ReturnType(Args...)>(obj, p);
}

}  // namespace mtps

#endif
