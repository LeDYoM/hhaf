#pragma once

#ifndef LIB_SCENE_SCENEFACTORY_INCLUDE_HPP
#define LIB_SCENE_SCENEFACTORY_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/scene.hpp>

namespace lib::scene
{
	using InterfaceType = Scene;
	using SceneConstructorFunction = function<uptr<InterfaceType>()>;

	class SceneFactory
	{
	public:
		SceneFactory();
		~SceneFactory();

		bool registerSceneType(str type_name, SceneConstructorFunction scene_constructor_function);

		template <typename T>
		constexpr bool registerSceneType(SceneConstructorFunction scene_constructor_function)
		{
			return registerSceneType(T::StaticTypeName, std::move(scene_constructor_function));
		}

		template <typename T>
		constexpr bool registerSceneType(str type_name)
		{
			return registerSceneType(std::move(type_name), T::create);
		}

		template <typename T>
		constexpr bool registerSceneType()
		{
			return registerSceneType(T::StaticTypeName, T::create);
		}

		uptr<InterfaceType> create(const str &type_name);

		template <typename T>
		constexpr uptr<InterfaceType> create()
		{
			return create(T::StaticTypeName);
		}

	private:
		struct SceneFactoryPrivate;
		uptr<SceneFactoryPrivate> private_;
	};
}

#endif
