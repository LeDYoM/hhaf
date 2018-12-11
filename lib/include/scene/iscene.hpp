#pragma once

#ifndef LIB_ISCENE_INTERFACE_INCLUDE_HPP
#define LIB_ISCENE_INTERFACE_INCLUDE_HPP

#include "iscenenode.hpp"

#define DECLARE_SCENE(sceneName) DECLARE_SCENE_NODE_FROM(sceneName, lib::scene::Scene)
		
#endif

