#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "vector3D.h"
#include <PxPhysicsAPI.h>
#include "ParticleSystem.h"
#include "SolidSystem.h"
#include "ForceSystem.h"

class LevelManager
{
public:
	LevelManager(physx::PxPhysics* gPhysics, physx::PxScene* gScene, SolidSystem* solidSystem, ForceSystem* forceSystem, ParticleSystem* particleSystem);
	~LevelManager();
private:
	void createWall(Vector3D pos, Vector3D halfDimensions, Vector4 color);
	void createBoxes();
	void createLimits();
	void createForces();
	void createParticles();

	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;

	SolidSystem* solidSystem;
	ForceSystem* forceSystem;
	ParticleSystem* particleSystem;

	std::vector<RenderItem*> renderItems;
	std::vector<physx::PxRigidActor*> limits;
};