#pragma once

#ifndef LIB_ISCENE_INTERFACE_INCLUDE_HPP
#define LIB_ISCENE_INTERFACE_INCLUDE_HPP

#define STRINGIFY(...) #__VA_ARGS__
#define DECLARE_SCENE(sceneName)	static constexpr char StaticTypeName[] = #sceneName;	\
	\
		static uptr<Scene> createScene()	\
		{	\
			return muptr<sceneName>();	\
		}

#endif

