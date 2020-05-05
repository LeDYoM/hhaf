#pragma once

#ifndef HAF_SCENE_COMPONENTCONTAINER_INCLUDE_HPP
#define HAF_SCENE_COMPONENTCONTAINER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/utils/include/componentcontainer_base.hpp>

namespace haf::scene
{
using ComponentContainer = ComponentContainerBase<true>;
using StaticComponentContainer = ComponentContainerBase<false>;

}  // namespace haf::scene

#endif
