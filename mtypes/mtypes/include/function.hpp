#pragma once

#include <iostream>
#include <memory>
#include <cassert>

#ifndef MTYPES_FUNCTION_INCLUDE_HPP__
#define MTYPES_FUNCTION_INCLUDE_HPP__

namespace lib
{
	template <typename T>
	class function;

	template <typename ReturnValue, typename... Args>
	class function<ReturnValue(Args...)> {
	public:

		constexpr function() : callable_{ nullptr } {}
		constexpr function(const function&) = default;
		constexpr function& operator=(const function&) = default;
		constexpr function(function&&) = default;
		constexpr function& operator=(function&&) = default;

		constexpr operator bool() const { return callable_ != nullptr; }

		template <typename T>
		constexpr function(T t) {
			callable_ = msptr<CallableT<T>>(t);
		}

		ReturnValue operator()(Args... args) const {
			assert(callable_);
			return callable_->Invoke(args...);
		}

	private:
		class ICallable {
		public:
			virtual ~ICallable() = default;
			virtual ReturnValue Invoke(Args...) = 0;
		};

		template <typename T>
		class CallableT final : public ICallable {
		public:
			constexpr CallableT(const T& t) : t_(t) {}

			constexpr CallableT(const CallableT&) = default;
			constexpr CallableT& operator=(const CallableT&) = default;
			constexpr CallableT(CallableT&&) = default;
			constexpr CallableT& operator=(CallableT&&) = default;

			~CallableT() override = default;

			constexpr ReturnValue Invoke(Args... args) {
				return t_(args...);
			}

		private:
			T t_;
		};

		sptr<ICallable> callable_;
	};
}

#endif
