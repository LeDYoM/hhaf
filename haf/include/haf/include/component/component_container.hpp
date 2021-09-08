#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/p_impl_pointer.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/utils/attachable_manager.hpp>
#include <typeindex>

namespace haf::component
{
/**
 * @brief class representing a container for components.
 * @see IComponent
 */
class HAF_API ComponentContainer : private utils::AttachableManager<IComponent>
{
    using BaseClass      = utils::AttachableManager<IComponent>;
    using AttachableType = typename BaseClass::AttachableType;

public:
    explicit ComponentContainer(
        htps::rptr<BaseClass::AttachableType> attachable);

    ~ComponentContainer();
    
    /**
     * @brief Create or get a reference to a component type. This method
     * could create an instance of the component and add it to the component
     * list or retrieve a pointer to it
     *
     * @tparam T Type of the component
     * @return Pointer to the component type. Either newly created or already
     * existing
     */
    template <typename T>
    htps::sptr<T> component()
    {
        htps::sptr<T> result{componentOfType<T>()};
        if (result == nullptr)
        {
            result = BaseClass::template create<T>();
            addComponent(result);
        }
        return result;
    }

    template <typename T>
    htps::sptr<T> componentOfType() const
    {
        htps::sptr<IComponent> cot{componentOfType(type_of<T>())};
        return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    /**
     * @brief Retrieve an instance of a component type. Either newly created
     * or already existing
     *
     * @tparam T Type of the component
     * @param element Return value as a reference. Template deduction will
     * get the required type.
     */
    template <typename T>
    void component(htps::sptr<T>& element)
    {
        if (element == nullptr)
        {
            element = component<T>();
        }
    }

    /**
     * @brief Update componentents of this container
     */
    void updateComponents();

    /**
     * @brief Clear all elements of this container     *
     */
    void clearComponents() noexcept;

private:
    template <typename T>
    std::type_index type_of() const noexcept
    {
        return std::type_index{typeid(T)};
    }

    bool addComponent(htps::sptr<IComponent> nc);
    htps::sptr<IComponent> componentOfType(std::type_index const& ti) const;

    struct ComponentContainerPrivate;
    htps::PImplPointer<ComponentContainerPrivate> p_;
};

}  // namespace haf::component

#endif
