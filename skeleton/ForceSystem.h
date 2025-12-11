#pragma once

#include "ForceGenerator.h"

#include "GravityForce.h"
#include "WindForce.h"
#include "WhirlwindForce.h"
#include "ExplosionForce.h"

#include "SpringForce.h"
#include "AnchoredSpringForce.h"
#include "BuoyancyForce.h"

#include "SolidBox.h"

class ForceSystem
{
public:
	ForceSystem() {};
	~ForceSystem();
	void update(double t);
	void updateParticle(double t, Particle* particle);
	void updateSolid(double t, SolidBox* box);
	void updateAnchoredSprings(double t, std::vector<Particle*> anchoredSpringParticles);
	void updateSprings(double t, std::vector<std::pair<Particle*, Particle*>> springParticles);

	void addGravityForceGenerator(Vector3D gravityForce);
	void addWindForceGenerator(Vector3D windVel, float linearDragCoeff, float quadraticDragCoeff = 0.0f);
	void addWhirlwindForceGenerator(float linearDragCoeff, float quadraticDragCoeff, Vector3D center, float strength, float radius);
	void addExplosionForceGenerator(Vector3D center, float strength, float radius, float decayTime);

	void addSpringForce(double k, double restingLength, Particle* other);
	void addAnchoredSpringForce(double k, double resting, const Vector3D& anchorPos);
	void addBuoyancyForce(float h, float V, float d);

	void increaseKfirstAnchoredSpring();

private:
	std::vector<ForceGenerator*> forceGenerators;
	std::vector<SpringForce*> springGenerators;
	std::vector<SpringForce*> anchoredSpringGenerators;
};

