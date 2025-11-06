#include "ForceSystem.h"

ForceSystem::~ForceSystem()
{
	for (auto forceGenerator : forceGenerators)
	{
		delete forceGenerator;
	}
}

void ForceSystem::update(double t, Particle* particle)
{
	for (auto forceGenerator : forceGenerators)
	{
		forceGenerator->update(t);
		forceGenerator->processForce(t, particle);
	}
}

void ForceSystem::addGravityForceGenerator(Vector3D gravityForce)
{
	forceGenerators.emplace_back(new GravityForce(gravityForce));
}

void ForceSystem::addWindForceGenerator(Vector3D windVel, float linearDragCoeff, float quadraticDragCoeff)
{
	forceGenerators.emplace_back(new WindForce(windVel, linearDragCoeff, quadraticDragCoeff));
}

void ForceSystem::addWhirlwindForceGenerator(float linearDragCoeff, float quadraticDragCoeff, Vector3D center, float strength, float radius)
{
	forceGenerators.emplace_back(new WhirlwindForce(linearDragCoeff, quadraticDragCoeff, center, strength, radius));
}

void ForceSystem::addExplosionForceGenerator(Vector3D center, float strength, float radius, float decayTime)
{
	forceGenerators.emplace_back(new ExplosionForce(center, strength, radius, decayTime));
}
