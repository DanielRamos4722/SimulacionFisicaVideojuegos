#pragma once

#include "core.hpp"
#include <PxPhysicsAPI.h>
#include "vector3D.h"

class PlayerManager
{
public:
	bool keys[256] = { false };

	void onKeyDown(unsigned char key) {
		keys[toupper(key)] = true;
	}

	void onKeyUp(unsigned char key) {
		keys[toupper(key)] = false;
	}

	PlayerManager(physx::PxPhysics* gPhysics, physx::PxScene* gScene, Camera* camera, Vector3D initPos);
	void update(double t);
	void processKey(unsigned char key);
	
private:
	void move();
	void updateCamera();
	bool grounded();

	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;
	physx::PxRigidDynamic* playerBody;
	Camera* mCamera;

	float speed;
	float jumpForce;
	unsigned char currentKey;
};