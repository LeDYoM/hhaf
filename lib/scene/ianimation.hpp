#ifndef LIB_IANIMATION_INCLUDE_HPP__
#define LIB_IANIMATION_INCLUDE_HPP__

#include <mtypes/include/timer.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

namespace lib
{
    namespace scene
    {
        namespace anim
        {
            using ActionFunc = function<void()>;
            class IAnimation
            {
            public:
                IAnimation(Time duration, ActionFunc endAction = {}) noexcept
                    : m_duration{ std::move(duration) }, m_timer{}, m_endAction{ std::move(endAction) } {}

                virtual bool animate()
                {
                    m_currentTime = m_timer.getElapsedTime();
                    if (m_currentTime > m_duration) {
                        m_delta = 1.0f;
                        return false;
                    }
                    m_delta = (static_cast<decltype(m_delta)>(
                            m_currentTime.asMilliSeconds()) / m_duration.asMilliSeconds()
                        );
                    return true;
                }

                constexpr void executeEndAction() {
                    if (m_endAction) {
                        m_endAction();
                    }
                }

                virtual ~IAnimation() {}
            protected:
                Time m_duration;
                Time m_currentTime;
                f32 m_delta{ 0.0f };
                Timer m_timer;
                ActionFunc m_endAction;
            };

            template <typename T>
            class IPropertyAnimation : public IAnimation
            {
            public:
                IPropertyAnimation(Time duration, IProperty<T> &prop, 
                    T start, T end, ActionFunc endAction = {})
                    : IAnimation{ std::move(duration), std::move(endAction) }, m_property{ prop }, m_startValue { std::move(start)	},
                    m_endValue{ std::move(end) }, m_deltaValue{ m_endValue - m_startValue } {}

                virtual bool animate() override
                {
                    const bool bResult{ IAnimation::animate() };
                    m_property.set(T{ m_startValue + (m_deltaValue * m_delta) });
                    return bResult;
                }

            protected:
                IProperty<T> &m_property;
                T m_startValue;
                T m_endValue;
                T m_deltaValue;
            };
        }
    }
}

#endif
