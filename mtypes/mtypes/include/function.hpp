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
		constexpr function(const function&t) noexcept = default;
		constexpr function& operator=(const function&) noexcept = default;
		constexpr function(function&&) noexcept = default;
		constexpr function& operator=(function&&) noexcept = default;

		constexpr operator bool() const noexcept { return m_callable != nullptr; }

		template <typename T, typename = typename std::enable_if< std::is_same_v<T, function> >::type >
		constexpr function(const T&t) noexcept : m_callable{ t.m_callable } {}

		template <typename T, typename = typename std::enable_if< !std::is_same_v<T,function> >::type >
		constexpr function(T&& t) {
			m_callable = msptr<CallableT<T>>(std::forward<T>(t));
		}

		constexpr ReturnValue operator()(Args&&... args) const {
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

			constexpr CallableT(const CallableT&)  noexcept = default;
			constexpr CallableT& operator=(const CallableT&)  noexcept = default;
			constexpr CallableT(CallableT&&)  noexcept = default;
			constexpr CallableT& operator=(CallableT&&)  noexcept = default;

			~CallableT() override = default;

			constexpr ReturnValue Invoke(Args... args) override {
				return m_t(args...);
			}

		private:
			T m_t;
		};

		sptr<ICallable> m_callable;
	};
}

#endif
