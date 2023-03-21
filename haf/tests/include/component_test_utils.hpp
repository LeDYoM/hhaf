HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_TESTS_UTILS_INCLUDE_HPP
#define HAF_COMPONENT_TESTS_UTILS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_base.hpp>
#include <haf/include/component/component_with_requirements.hpp>
#include <haf/include/scene/scene_node.hpp>
#include "system_test_utils.hpp"

namespace haf::test
{
namespace detail
{
template <typename T>
void autoRegisterComponentRequirements(
    scene::SceneManager& scene_manager,
    component::MultipleComponentRequirement<T>&)
{
    scene_manager.registerComponent<T>();
}

template <>
constexpr void autoRegisterComponentRequirements<component::NullStruct>(
    scene::SceneManager&,
    component::MultipleComponentRequirement<component::NullStruct>&)
{}

template <typename T, typename... Args>
void autoRegisterComponentRequirements(
    scene::SceneManager& scene_manager,
    component::MultipleComponentRequirement<T, Args...>& element)
{
    scene_manager.registerComponent<T>();
    autoRegisterComponentRequirements(
        scene_manager,
        static_cast<component::MultipleComponentRequirement<Args...>&>(
            element));
}

template <typename... Args>
void autoRegisterComponentRequirements(
    scene::SceneManager& scene_manager,
    component::ComponentWithRequirements<Args...>& element)
{
    autoRegisterComponentRequirements(
        scene_manager,
        static_cast<component::ComponentWithRequirements<Args...>::BaseClass&>(
            element));
}

template <typename T>
void autoRegisterComponentRequirements(scene::SceneManager& scene_manager,
                                       T& element)
{
    autoRegisterComponentRequirements(scene_manager,
                                      static_cast<T::BaseClass&>(element));
}
}  // namespace detail

template <typename T>
struct CreateComponentForTestResult
    : public CreateSystemForTestResult<TestSceneManager>
{
    core::sptr<T> component;
};

template <typename T>
CreateComponentForTestResult<T> createComponentForTest()
{
    auto t_system{createSystemForTest<TestSceneManager>()};
    scene::SceneManager& scene_manager{t_system.system};
    core::rptr<haf::scene::SceneNode> root_scene_node{
        scene_manager.rootSceneNode()};

    scene_manager.registerComponent<T>();
    T a{};
    detail::autoRegisterComponentRequirements(scene_manager, a);

    auto component{root_scene_node->attachComponent<T>()};
    CHECK(component != nullptr);

    return {{core::move(t_system)}, core::move(component)};
}
}  // namespace haf::test

#endif
