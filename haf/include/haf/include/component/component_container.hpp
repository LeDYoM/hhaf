#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/p_impl_pointer.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/utils/attachable_manager.hpp>
#include <haf/include/utils/type_data.hpp>

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

    /**
     * @brief Destroy the Component Container object
     * @note It is not virtual because the base class is private
     */
    ~ComponentContainer();
    
    /**
     * @brief Create or get a pointer to a component type. This method
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

    /**
     * @brief Retrieve the attached instance of a component if it exists.
     * 
     * @tparam T Type of the component
     * @return Pointer to the component or nullptr
     */
    template <typename T>
    htps::sptr<T> componentOfType() const
    {
        auto cot{componentOfType(type_of<T>())};
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
    utils::type_index type_of() const noexcept
    {
        return utils::type_index{typeid(T)};
    }

    bool addComponent(htps::sptr<IComponent> nc);
    htps::sptr<IComponent> componentOfType(utils::type_index const& ti) const;

    struct ComponentContainerPrivate;
    htps::PImplPointer<ComponentContainerPrivate> p_;
};

}  // namespace haf::component

#endif
