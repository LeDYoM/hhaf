HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <haf/include/component/component.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{
/**
 * @brief class representing a container for components.
 * @see Component
 */
class HAF_API ComponentContainer
{
public:
    static constexpr char StaticTypeName[] = "ComponentContainer";

    explicit ComponentContainer(htps::rptr<scene::SceneNode> attachable);

    /**
     * @brief Destroy the Component Container object
     */
    virtual ~ComponentContainer();

    core::sptr<Component> attachComponent(core::str_view typeName);

    template <typename T>
    core::sptr<T> attachComponent()
    {
        core::sptr<Component> result{attachComponent(T::StaticTypeName)};
        return result ? core::dynamic_pointer_cast<T>(result) : nullptr;
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
        auto cot{componentOfType(T::StaticTypeName)};
        return cot ? core::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    /**
     * @brief Retrieve the attached instance of a component if it exists.
     *
     * @tparam T Type of the component
     * @param element Pointer where the output wil be stored. It will be nullptr
     * if the component does not exist.
     */
    template <typename T>
    void componentOfType(htps::sptr<T>& element) const
    {
        element = componentOfType<T>();
    }

    core::sptr<Component> componentOfType(core::str_view typeName) const;

    /**
     * @brief Update componentents of this container
     */
    void updateComponents();

    /**
     * @brief Clear all elements of this container
     */
    void clearComponents() noexcept;

    core::size_type components() const noexcept;
    core::str_view componentNameAt(core::size_type const index) const;

    core::sptr<Component> getOrCreateComponent(core::str_view typeName);

    template <typename T>
    core::sptr<T> safeComponentConversion(
        core::sptr<Component> source_component)
    {
        return source_component
            ? core::dynamic_pointer_cast<T>(source_component)
            : nullptr;
    }

private:
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
    core::sptr<T> getOrCreateComponent()
    {
        core::sptr<Component> result{getOrCreateComponent(T::StaticTypeName)};
        return result ? core::dynamic_pointer_cast<T>(result) : nullptr;
    }

    core::sptr<Component> createComponent(core::str_view typeName);
    bool applyRequirements(Component& _thisComponent);
    bool addComponent(htps::sptr<Component> nc);

    struct ComponentContainerPrivate;
    htps::PImplPointer<ComponentContainerPrivate> p_;
};

}  // namespace haf::component

#endif
