#pragma once

#include "ForceGenerator.h"

class GravityForce : public ForceGenerator
{
public:
	GravityForce(Vector3D gravityForce) : gravityForce(gravityForce) {};
	void processForce(double t, Particle* particle) override;
private:
	Vector3D gravityForce;
};

