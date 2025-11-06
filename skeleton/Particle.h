#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "core.hpp"
#include "vector3D.h"

using namespace physx;

class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, float mass, float damp, Vector4 color = { 1.0f, 0.0f, 0.0f, 1.0f }, PxReal size = 2.0f, double lifeSpan = 3000.0f, float maxDistance = 10.0f);
	~Particle();

	void updateTime(double t);
	virtual void integrate(double t);
	bool checkAlive();

	Vector3D getCurrentPos() { return pose->p; };
	Vector3D getCurrentVel() { return vel; };
	float getMass() { return mass; };
	Vector3D getCurrentForce() { return force; };
	void addForce(Vector3D force) { this->force += force; };
	void setForce(Vector3D force) { this->force = force; };
	void resetForce() { force = Vector3D(); };
protected:
	Vector3D vel;
	Vector3D acc;
	float damp;
	PxTransform* pose;
	RenderItem* renderItem;

	Vector3D initPos;
	double aliveTime;

	double lifeSpan;
	float maxDistance;

	float mass;
	Vector3D force;

};

