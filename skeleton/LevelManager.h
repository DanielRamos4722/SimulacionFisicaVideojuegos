#pragma once

#include "core.hpp"
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "vector3D.h"

class LevelManager
{
public:
	LevelManager(physx::PxPhysics* gPhysics, physx::PxScene* gScene);
private:
	void createLimits();

	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;
};

