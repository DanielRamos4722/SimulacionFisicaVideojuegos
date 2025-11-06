#pragma once

#include "ForceGenerator.h"

#include "GravityForce.h"
#include "WindForce.h"
#include "WhirlwindForce.h"
#include "ExplosionForce.h"

class ForceSystem
{
public:
	ForceSystem() {};
	~ForceSystem();
	void update(double t, Particle* particle);
	void addGravityForceGenerator(Vector3D gravityForce);
	void addWindForceGenerator(Vector3D windVel, float linearDragCoeff, float quadraticDragCoeff = 0.0f);
	void addWhirlwindForceGenerator(float linearDragCoeff, float quadraticDragCoeff, Vector3D center, float strength, float radius);
	void addExplosionForceGenerator(Vector3D center, float strength, float radius, float decayTime);

private:
	std::vector<ForceGenerator*> forceGenerators;
};

