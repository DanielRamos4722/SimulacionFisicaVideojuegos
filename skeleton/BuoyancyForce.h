#pragma once

#include "ForceGenerator.h"

class BuoyancyForce : public ForceGenerator
{
public:
	BuoyancyForce(float h, float V, float d);
	void processForce(double t, SolidBox* box) override;
	void processForce(double t, Particle* particle) override;
	~BuoyancyForce() { delete liquidParticle; liquidParticle = nullptr; };
protected:
	float height;
	float volume;
	float liquidDensity;
	CONST float gravity = 9.81f;

	Particle* liquidParticle;
};

