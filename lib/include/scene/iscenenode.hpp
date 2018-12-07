#pragma once

#ifndef LIB_ISCENENODE_INTERFACE_INCLUDE_HPP
#define LIB_ISCENENODE_INTERFACE_INCLUDE_HPP

#define DECLARE_SCENE_NODE_FROM(SceneNodeTypeName, BaseSceneNodeTypeName) SceneNodeTypeName() : BaseSceneNodeTypeName{ lib::str(#SceneNodeTypeName) } {}	\
	\
	~SceneNodeTypeName() override {}	\
	\
	SIMPLE_DECLARE_SCENE_NODE_FROM(SceneNodeTypeName, BaseSceneNodeTypeName)

#define SIMPLE_DECLARE_SCENE_NODE_FROM(SceneNodeTypeName, BaseSceneNodeTypeName)	static constexpr char StaticTypeName[] = #SceneNodeTypeName;	\
	\
		static lib::uptr<BaseSceneNodeTypeName> createScene()	\
		{	\
			return lib::muptr<SceneNodeTypeName>();	\
		}

#define DECLARE_SCENE_NODE(SceneNodeTypeName) DECLARE_SCENE_NODE_FROM(SceneNodeTypeName, lib::scene::SceneNode)

#endif

