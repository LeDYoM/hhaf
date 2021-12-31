#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/utils/type_data.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene
{
    class SceneNode;
}

namespace haf::component
{
/**
 * @brief class representing a container for components.
 * @see IComponent
 */
class HAF_API ComponentContainer
{
    using AttachableType = scene::SceneNode;

public:
    explicit ComponentContainer(htps::rptr<AttachableType> attachable);

    /**
     * @brief Destroy the Component Container object
     */
    virtual ~ComponentContainer();

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
    types::sptr<T> component()
    {
        types::sptr<T> result{componentOfType<T>()};
        if (result == nullptr)
        {
            result = create<T>();
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
    types::sptr<T> componentOfType() const
    {
        auto cot{componentOfType(type_of<T>())};
        return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    /**
     * @brief Retrieve the attached instance of a component if it exists.
     *
     * @tparam T Type of the component
     * @param element Pointer where the output wil be stored. It will be nullptr
     * if the component does not exist.
     */
    template <typename T>
    void componentOfType(types::sptr<T>& element) const
    {
        element = componentOfType<T>();
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

protected:
    template <typename T>
    auto create() const
    {
        // Static check that T is a valid type for this class.
        static_assert(std::is_base_of_v<IComponent, T>,
                      "You can only use this "
                      "function with types derived from AttachedBase");

        auto result{htps::muptr<T>()};
        initialize(*result);
        return result;
    }

private:
    void initialize(IComponent& dw) const
    {
        dw.setAttachedNode(attachable_);
    }

    template <typename T>
    utils::type_index type_of() const noexcept
    {
        return utils::type_index{typeid(T)};
    }

    bool addComponent(htps::sptr<IComponent> nc);
    types::sptr<IComponent> componentOfType(utils::type_index const& ti) const;

    const htps::rptr<scene::SceneNode> attachable_;

    struct ComponentContainerPrivate;
    types::PImplPointer<ComponentContainerPrivate> p_;
};

}  // namespace haf::component

#endif
