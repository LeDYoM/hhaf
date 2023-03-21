HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_WITH_REQUIREMENTS_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_WITH_REQUIREMENTS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_requirements.hpp>

namespace haf::component
{
template <typename T>
class SingleComponentRequirement
{
public:
    constexpr auto getComponent() noexcept { return m_component; }

    constexpr core::sptr<T const> const getComponent() const noexcept
    {
        return m_component;
    }

    bool addRequirement(ComponentRequirements& component_requirements)
    {
        return component_requirements.getOrCreateComponent(m_component);
    }

private:
    core::sptr<T> m_component;
};

template <typename T, typename... Args>
class MultipleComponentRequirement
    : public SingleComponentRequirement<T>,
      public MultipleComponentRequirement<Args...>
{
    using MultipleBase = MultipleComponentRequirement<Args...>;

public:
    template <typename U>
    constexpr auto getComponent() noexcept
    {
        if constexpr (std::is_same_v<U, T>)
        {
            return SingleComponentRequirement<T>::getComponent();
        }
        else
        {
            return MultipleBase::template getComponent<U>();
        }
    }

    template <typename U>
    constexpr auto getComponent() const noexcept
    {
        if constexpr (std::is_same_v<U, T const>)
        {
            return SingleComponentRequirement<T>::getComponent();
        }
        else
        {
            return MultipleBase::template getComponent<U const>();
        }
    }

    constexpr bool addRequirements(
        ComponentRequirements& component_requirements)
    {
        return SingleComponentRequirement<T>::addRequirement(
                   component_requirements) &&
            MultipleBase::addRequirements(component_requirements);
    }
};

template <typename T>
class MultipleComponentRequirement<T> : public SingleComponentRequirement<T>
{
public:
    template <typename U>
    constexpr auto getComponent() noexcept
    {
        return SingleComponentRequirement<T>::getComponent();
    }

    template <typename U>
    constexpr auto getComponent() const noexcept
    {
        return SingleComponentRequirement<T>::getComponent();
    }

    constexpr bool addRequirements(
        ComponentRequirements& component_requirements)
    {
        return SingleComponentRequirement<T>::addRequirement(
            component_requirements);
    }
};
struct NullStruct
{};

template <>
class MultipleComponentRequirement<NullStruct>
{
public:
    constexpr bool addRequirements(ComponentRequirements&) { return true; }
};

template <typename... Args>
class ComponentWithRequirements
    : public MultipleComponentRequirement<Args..., NullStruct>,
      public Component
{
public:
    using BaseClass = MultipleComponentRequirement<Args..., NullStruct>;

    template <typename T>
    constexpr auto getComponent() noexcept
    {
        return BaseClass::template getComponent<T>();
    }

    template <typename T>
    constexpr auto getComponent() const noexcept
    {
        return BaseClass::template getComponent<T const>();
    }

    constexpr bool addRequirements(
        ComponentRequirements& component_requirements) override final
    {
        return BaseClass::addRequirements(component_requirements);
    }
};
}  // namespace haf::component

#endif
