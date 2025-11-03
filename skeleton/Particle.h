#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "core.hpp"
#include "vector3D.h"

using namespace physx;

class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damp, Vector4 color = { 1.0f, 0.0f, 0.0f, 1.0f }, PxReal size = 2.0f);
	~Particle();

	virtual void integrate(double t);
protected:
	Vector3D vel;
	Vector3D acc;
	float damp;
	PxTransform pose;
	RenderItem* renderItem;
};

