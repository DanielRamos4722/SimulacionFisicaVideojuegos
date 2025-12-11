#include "ForceSystem.h"

ForceSystem::~ForceSystem()
{
	for (auto forceGenerator : forceGenerators)
	{
		delete forceGenerator;
	}
}

void ForceSystem::update(double t)
{
	for (auto forceGenerator : forceGenerators)
	{
		forceGenerator->update(t);
	}
}

void ForceSystem::updateParticle(double t, Particle* particle)
{
	for (auto forceGenerator : forceGenerators)
	{
		forceGenerator->processForce(t, particle);
	}
}

void ForceSystem::updateSolid(double t, SolidBox* box)
{
	for (auto forceGenerator : forceGenerators)
	{
		forceGenerator->processForce(t, box);
	}
}

void ForceSystem::updateAnchoredSprings(double t, std::vector<Particle*> anchoredSpringParticles)
{
	for (int i = 0; i < anchoredSpringGenerators.size(); i++)
	{
		anchoredSpringGenerators[i]->update(t);
		anchoredSpringGenerators[i]->processForce(t, anchoredSpringParticles[i]);
	}
}

void ForceSystem::updateSprings(double t, std::vector<std::pair<Particle*, Particle*>> springParticles)
{
	for (int i = 0; i < springGenerators.size(); i++)
	{
		springGenerators[i]->update(t);
		springGenerators[i]->processForce(t, springParticles[i].first);
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

void ForceSystem::addSpringForce(double k, double restingLength, Particle* other)
{
	springGenerators.emplace_back(new SpringForce(k, restingLength, other));
}

void ForceSystem::addAnchoredSpringForce(double k, double resting, const Vector3D& anchorPos)
{
	anchoredSpringGenerators.emplace_back(new AnchoredSpringForce(k, resting, anchorPos));
}

void ForceSystem::addBuoyancyForce(float h, float V, float d)
{
	forceGenerators.emplace_back(new BuoyancyForce(h, V, d));
}

void ForceSystem::increaseKfirstAnchoredSpring()
{
	if (anchoredSpringGenerators[0] != nullptr)
	{
		anchoredSpringGenerators[0]->increaseK();
	}
}
