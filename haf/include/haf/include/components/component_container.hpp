#ifndef HAF_SCENE_COMPONENTCONTAINER_INCLUDE_HPP
#define HAF_SCENE_COMPONENTCONTAINER_INCLUDE_HPP

#include <hlog/include/hlog.hpp>
#include <haf/include/components/icomponent.hpp>
#include <haf/include/utils/attachable_manager.hpp>
#include <htypes/include/lockablevector.hpp>
#include <htypes/include/types.hpp>
#include <typeindex>

namespace haf::component
{
/**
 * @brief Templated class representing a templated part of a component
 * container.
 * A component container part contains methods to manage the components
 * added to it.
 *
 * @tparam WithUpdate Specify if the components to add in this component
 * container should contain update function or not and if this function will
 * be updated.
 */
class ComponentContainer : public utils::AttachableManager<IComponent>
{
public:
    using ComponentType  = IComponent;
    using BaseClass      = utils::AttachableManager<ComponentType>;
    using AttachableType = typename BaseClass::AttachableType;

    using BaseClass::AttachableManager;

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
    void component(htps::sptr<T>& element)
    {
        if (element == nullptr)
        {
            element = component<T>();
        }
    }

    void updateComponents()
    {
        components_.performUpdate([](htps::sptr<IComponent> const& component) {
            component->update();
        });
    }

    void clearComponents() noexcept { components_.clear(); }

private:
    /**
     * Returns the component of the specified type if exists
     * @tparam T type of the component to be retrieved
     * @return A shared pointer to the container or nullptr if not found
     */
    template <typename T>
    htps::sptr<T> componentOfType() const
    {
        htps::sptr<ComponentType> cot(
            componentOfType(std::type_index(typeid(T))));
        return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    std::type_index tindexOf(const htps::sptr<ComponentType>& c) const
    {
        return std::type_index(typeid(*c));
    }

    htps::sptr<ComponentType> getComponentFromTypeIndex(
        const std::type_index& tindex) const
    {
        const auto v{components_.next()};
        auto iterator(v.find_if(
            v.cbegin(), v.cend(),
            [this, &tindex](const htps::sptr<ComponentType>& component) {
                return tindexOf(component) == tindex;
            }));
        return (iterator == v.cend()) ? nullptr : (*iterator);
    }

    htps::sptr<ComponentType> componentOfType(
        const std::type_index& ti) const
    {
        return getComponentFromTypeIndex(ti);
    }

    bool addComponent(htps::sptr<ComponentType> nc)
    {
        LogAsserter::log_assert(nc != nullptr,
                                "Trying to add a nullptr component");
        components_.emplace_back(std::move(nc));
        return true;
    }

    htps::LockableVector<htps::sptr<ComponentType>> components_;
};

}  // namespace haf::component

#endif
