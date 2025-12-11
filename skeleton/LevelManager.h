#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "vector3D.h"
#include <PxPhysicsAPI.h>
#include "SolidSystem.h"

class LevelManager
{
public:
	LevelManager(physx::PxPhysics* gPhysics, physx::PxScene* gScene, SolidSystem* solidSystem);
	~LevelManager();
private:
	void createWall(Vector3D pos, Vector3D halfDimensions, Vector4 color);
	void createBoxes();
	void createLimits();

	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;

	SolidSystem* solidSystem;

	std::vector<RenderItem*> renderItems;
	std::vector<physx::PxRigidActor*> limits;
};