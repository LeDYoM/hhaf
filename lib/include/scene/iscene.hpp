#pragma once

#ifndef LIB_ISCENE_INTERFACE_INCLUDE_HPP
#define LIB_ISCENE_INTERFACE_INCLUDE_HPP

#define DECLARE_SCENE(sceneName) sceneName() : lib::scene::Scene{ lib::str(#sceneName) } {}	\
	\
	~sceneName() override {}	\
	\
	SIMPLE_DECLARE_SCENE(sceneName)

#define SIMPLE_DECLARE_SCENE(sceneName)	static constexpr char StaticTypeName[] = #sceneName;	\
	\
		static lib::uptr<lib::scene::Scene> createScene()	\
		{	\
			return lib::muptr<sceneName>();	\
		}
		
#endif

