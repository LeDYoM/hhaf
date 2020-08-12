#pragma once

#ifndef HAF_STATES_CONTROLLER_INCLUDE_HPP
#define HAF_STATES_CONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <mtypes/include/stack.hpp>
#include <mtypes/include/lockablevector.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/scene/include/icomponent.hpp>

namespace haf
{
using Action = mtps::function<void()>;
}

namespace haf::scene
{
template <class T>
class StatesControllerRaw
{
public:
    virtual ~StatesControllerRaw() {}

    constexpr void update()
    {
        if (!m_pendingActions.current().empty())
        {
            for (auto action : m_pendingActions.current())
            {
                action();
                m_pendingActions.erase_value(action);
            }
            m_pendingActions.update();
        }
    }

    constexpr void start(T firstState) noexcept
    {
        LogAsserter::log_assert(
            m_statesStack.empty(),
            "You cannot call start if the stack is not empty");
        if (m_statesStack.empty())
        {
            BeforeStart();
            push_state(std::move(firstState));
        }
    }

    constexpr void push_state(T firstState) noexcept
    {
        postAction([this, first_state = std::move(firstState)]() mutable {
            if (!m_statesStack.empty())
            {
                StatePaused(m_statesStack.back());
            }
            StatePushed(first_state);
            StateStarted(first_state);
            m_statesStack.push_back(std::move(first_state));
        });
    }

    constexpr void pop_state() noexcept
    {
        postAction([this]() {
            LogAsserter::log_assert(m_statesStack.size() > 0U,
                                    "m_statesStack.size() is 0");
            StateFinished(m_statesStack.back());
            StatePopped(m_statesStack.back());
            if (m_statesStack.size() > 1U)
            {
                m_statesStack.pop_back();
                StateResumed(m_statesStack.back());
            }
            else
            {
                m_statesStack.pop_back();
                AfterFinish();
            }
        });
    }

    constexpr void setState(T newState) { changeState(std::move(newState)); }

    constexpr bool hasActiveState() const noexcept
    {
        return !m_statesStack.empty();
    }

    constexpr mtps::size_type stateStackSize() const noexcept
    {
        return m_statesStack.size();
    }

    constexpr const T& currentState() const noexcept
    {
        return m_statesStack.cback();
    }

    constexpr T& currentState() noexcept { return m_statesStack.back(); }

    mtps::emitter<const T&> StateFinished;
    mtps::emitter<const T&> StateStarted;
    mtps::emitter<const T&> StatePushed;
    mtps::emitter<const T&> StatePopped;
    mtps::emitter<const T&> StatePaused;
    mtps::emitter<const T&> StateResumed;
    mtps::emitter<> BeforeStart;
    mtps::emitter<> AfterFinish;

private:
    inline void changeState(T newState)
    {
        postAction([this, newState = std::move(newState)]() {
            LogAsserter::log_assert(m_statesStack.size() != 0U,
                                    "States stack size is 0");
            StateFinished(m_statesStack.back());
            m_statesStack.pop_back();
            StateStarted(newState);
            m_statesStack.push_back(std::move(newState));
        });
    }

    constexpr void postAction(Action action)
    {
        m_pendingActions.push_back(std::move(action));
    }

    mtps::stack<T> m_statesStack;
    mtps::LockableVector<Action> m_pendingActions;
};

template <typename T>
class StatesController : public StatesControllerRaw<T>, public IComponent
{
public:
    ~StatesController() override {}

    void update() override { StatesControllerRaw<T>::update(); }
};
}  // namespace haf::scene

#endif
