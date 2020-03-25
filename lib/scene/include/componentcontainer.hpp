#pragma once

#ifndef LIB_SCENE_COMPONENTCONTAINER_INCLUDE_HPP
#define LIB_SCENE_COMPONENTCONTAINER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/lockablevector.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/include/icomponent.hpp>
#include <lib/system/include/attachable_manager.hpp>
#include <typeinfo>
#include <typeindex>

namespace lib::scene
{
class SceneNode;
class ComponentContainer : public sys::AttachableManager<IComponent, false>
{
public:
    using BaseClass = sys::AttachableManager<IComponent, false>;

    using BaseClass::AttachableManager;

    template <typename T>
    mtps::sptr<T> addComponentOfType()
    {
        log_assert(componentOfType<T>() == nullptr,
                   "There is already a component with this type");
        auto nc(create<T>());
        addComponent(nc);
        return nc;
    }

    template <typename T>
    void ensureComponentOfType(mtps::sptr<T> &element)
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
        mtps::sptr<IComponent> cot(componentOfType(std::type_index(typeid(T))));
        return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    void clearComponents() noexcept { m_components.clear(); }

private:
    bool addComponent(mtps::sptr<IComponent> nc);

    template <typename T>
    void addComponentOfType(mtps::sptr<T> &component)
    {
        component = addComponentOfType<T>();
    }

    const mtps::sptr<IComponent> componentOfType(const std::type_index &ti) const;
   mtps::LockableVector<mtps::sptr<IComponent>> m_components;
};
} // namespace lib::scene

#endif
