#pragma once

#ifndef HAF_SCENE_COMPONENTCONTAINER_INCLUDE_HPP
#define HAF_SCENE_COMPONENTCONTAINER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/scene/include/componentcontainer_part.hpp>
#include <type_traits>

namespace haf::scene
{

class ComponentContainer
{
public:
    using ComponentType = typename ComponentContainerPart<true>::ComponentType;
    using StaticComponentType =
        typename ComponentContainerPart<false>::ComponentType;
    using AttachableType = ComponentContainerPart<true>::AttachableType;

    explicit ComponentContainer(mtps::rptr<AttachableType> init) :
        component_container_{init}, static_component_container_{init}
    {}

    void updateComponents()
    {
        component_container_.updateComponents();
        static_component_container_.updateComponents();
    }

    void clearComponents()
    {
        component_container_.clearComponents();
        static_component_container_.clearComponents();
    }

    template <typename T>
    mtps::sptr<T> componentOfType() const
    {
        return getComponentContainerForType<T>().componentOfType<T>();
    }

    template <typename T>
    mtps::sptr<T> addComponentOfType()
    {
        return getComponentContainerForType<T>().addComponentOfType<T>();
    }

    template <typename T>
    void ensureComponentOfType(mtps::sptr<T>& element)
    {
        getComponentContainerForType<T>().ensureComponentOfType(element);
    }

private:
    template <bool IsStatic>
    constexpr auto& getComponentContainer() noexcept;

    template <>
    constexpr auto& getComponentContainer<true>() noexcept
    {
        return static_component_container_;
    }

    template <>
    constexpr auto& getComponentContainer<false>() noexcept
    {
        return component_container_;
    }

    template <bool IsStatic>
    constexpr const auto& getComponentContainer() const noexcept;

    template <>
    constexpr const auto& getComponentContainer<true>() const noexcept
    {
        return static_component_container_;
    }

    template <>
    constexpr const auto& getComponentContainer<false>() const noexcept
    {
        return component_container_;
    }

    template <typename T>
    constexpr const auto& getComponentContainerForType() const noexcept
    {
        return getComponentContainer<
            std::is_convertible_v<T, StaticComponentType>>();
    }

    template <typename T>
    constexpr auto& getComponentContainerForType() noexcept
    {
        return getComponentContainer<
            std::is_convertible_v<T, StaticComponentType>>();
    }

    ComponentContainerPart<true> component_container_;
    ComponentContainerPart<false> static_component_container_;
};

}  // namespace haf::scene

#endif
