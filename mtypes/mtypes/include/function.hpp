#pragma once

#ifndef MTYPES_FUNCTION_INCLUDE_HPP__
#define MTYPES_FUNCTION_INCLUDE_HPP__

#include <cassert>
#include "types.hpp"

namespace lib
{
	template <typename>
	class function;

	template <typename ReturnValue, typename... Args>
	class function<ReturnValue(Args...)> final {
	public:
		constexpr function() noexcept : m_callable{ nullptr } {}
		constexpr function(std::nullptr_t) noexcept : m_callable{ nullptr } {}

		constexpr operator bool() const noexcept { return m_callable != nullptr; }

		template <typename T, typename V>
		constexpr function(T*const t, V function) : m_callable{ msptr<CallableMethodPointerT<T>>(t, function) } {}

		template <typename T>
		constexpr function(T t) : m_callable { msptr<CallableT<T>>(std::move(t)) } {}

		constexpr ReturnValue operator()(Args... args) const {
			assert(m_callable);
			return m_callable->Invoke(std::forward<Args>(args)...);
		}

	private:
		class ICallable {
		public:
			virtual ~ICallable() = default;
			virtual constexpr ReturnValue Invoke(Args...) = 0;
		};

		template <typename T>
		class CallableT final : public ICallable {
		public:
			template <typename Y>
			constexpr CallableT(Y &&t) noexcept : m_t{ std::forward<Y>(t) } {}

			~CallableT() override = default;

			constexpr ReturnValue Invoke(Args... args) override {
				return m_t(std::forward<Args>(args)...);
			}

		private:
			T m_t;
		};

		template <class T>
		class CallableMethodPointerT : public ICallable
		{
		public:
			typedef ReturnValue (T::*HandlerFunctionPtr)(Args...);

			CallableMethodPointerT(T* receiver, HandlerFunctionPtr function) : obj{ receiver }, function_{ function } {}

			constexpr ReturnValue Invoke(Args... args) override
			{
				return (obj->*function_)(std::forward<Args>(args)...);
			}

		private:
			T*const obj;
			HandlerFunctionPtr function_;
		};


		sptr<ICallable> m_callable;
	};

	template <class T, typename... Args>
	class EventHandlerImpl
	{
	public:
		typedef void (T::*HandlerFunctionPtr)(Args...);

		/// Construct with receiver and function pointers.
		EventHandlerImpl(T* receiver, HandlerFunctionPtr function) :
			obj(receiver),
			function_(function)
		{
		}

		virtual void Invoke(Args... args)
		{
			(obj->*function_)(std::forward<Args>(args)...);
		}

	private:
		T*obj;
		/// Class-specific pointer to handler function.
		HandlerFunctionPtr function_;
	};

	template <class T, typename R, typename... Args>
	function<R(Args...)> EventHandler(T*obj, typename EventHandlerImpl<T, R, Args...>::HandlerFunctionPtr f)
	{
		EventHandlerImpl<T, R, Args...> p(obj, f);
		return [&p](Args...) { return p.Invoke(std::forward<Args>(args)...); }
	}

}

#endif
