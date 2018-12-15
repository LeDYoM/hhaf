#include "scenefactory.hpp"
#include "scene.hpp"

#include <lib/include/core/log.hpp>

#include <map>

namespace lib::scene
{
	struct SceneFactory::SceneFactoryPrivate
	{
		std::map<str, SceneConstructorFunction> constructors_;

		inline bool containsSceneType(const str& name)
		{
			return constructors_.find(name) != std::end(constructors_);
		}

		inline void insert(str name, SceneConstructorFunction scene_cf)
		{
			constructors_[std::move(name)] = scene_cf;
		}

		inline SceneConstructorFunction get(str name)
		{
			return constructors_[std::move(name)];
		}
	};

	SceneFactory::SceneFactory() 
		: private_{ muptr<SceneFactoryPrivate>() } {}

	SceneFactory::~SceneFactory() = default;

	bool SceneFactory::registerSceneType(str type_name, SceneConstructorFunction scene_constructor_function)
	{
		if (private_->containsSceneType(type_name))
		{
			return false;
		}

		private_->insert(std::move(type_name), std::move(scene_constructor_function));
		return true;
	}

	uptr<InterfaceType> SceneFactory::create(const str &type_name)
	{
		if (!private_->containsSceneType(type_name))
		{
			return uptr<InterfaceType>(nullptr);
		}

		auto constructor(private_->get(type_name));
		if (!constructor)
		{
			return uptr<InterfaceType>(nullptr);
		}

		return constructor();
	}
}
