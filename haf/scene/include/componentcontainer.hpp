#pragma once

#ifndef HAF_SCENE_COMPONENTCONTAINER_INCLUDE_HPP
#define HAF_SCENE_COMPONENTCONTAINER_INCLUDE_HPP

#include <hlog/include/hlog.hpp>
#include <haf/scene/include/icomponent.hpp>
#include <haf/utils/include/attachable_manager.hpp>
#include <mtypes/include/lockablevector.hpp>
#include <mtypes/include/types.hpp>
#include <typeindex>
#include <typeinfo>

namespace haf::scene
{
class SceneNode;

template <bool WithUpdate>
class ComponentContainerBase
    : public sys::AttachableManager<IComponentBase<WithUpdate>>
{
public:
    using BaseClass     = sys::AttachableManager<IComponentBase<WithUpdate>>;
    using ComponentType = IComponentBase<WithUpdate>;

    using BaseClass::AttachableManager;

    template <typename T>
    mtps::sptr<T> addComponentOfType()
    {
        LogAsserter::log_assert(componentOfType<T>() == nullptr,
                                "There is already a component with this type");
        mtps::sptr<T> nc(create<T>());
        addComponent(nc);
        return nc;
    }

    template <typename T>
    void ensureComponentOfType(mtps::sptr<T>& element)
    {
        if (!element)
        {
            element = addComponentOfType<T>();
        }
    }

    void updateComponents();

    /**
     * Returns the component of the specified type if exists
     * @param T type of the component to be retrieved
     * @return A shared pointer to the container or nullptr if not found
     */
    template <typename T>
    mtps::sptr<T> componentOfType() const
    {
        mtps::sptr<ComponentType> cot(
            componentOfType(std::type_index(typeid(T))));
        return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    void clearComponents() noexcept { m_components.clear(); }

private:
    bool addComponent(mtps::sptr<ComponentType> nc)
    {
        LogAsserter::log_assert(nc != nullptr,
                                "Trying to add a nullptr component");
        m_components.emplace_back(std::move(nc));
        return true;
    }

    template <typename T>
    void addComponentOfType(mtps::sptr<T>& component)
    {
        component = addComponentOfType<T>();
    }

    std::type_index tindexOf(const mtps::sptr<ComponentType>& c) const
    {
        return std::type_index(typeid(*c));
    }

    mtps::sptr<ComponentType> getComponentFromTypeIndex(
        const std::type_index& tindex,
        const mtps::vector_shared_pointers<IComponent>& v) const
    {
        auto iterator(std::find_if(
            v.cbegin(), v.cend(),
            [this, &tindex](const mtps::sptr<ComponentType>& component) {
                return tindexOf(component) == tindex;
            }));
        return (iterator == v.cend()) ? nullptr : (*iterator);
    }

    const mtps::sptr<ComponentType> componentOfType(
        const std::type_index& ti) const
    {
        return getComponentFromTypeIndex(ti, m_components.next());
    }

    mtps::LockableVector<mtps::sptr<ComponentType>> m_components;
};

using ComponentContainer = ComponentContainerBase<true>;

}  // namespace haf::scene

#endif
