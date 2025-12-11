#pragma once

#include "Particle.h"
#include "SolidBox.h"

class ForceGenerator
{
public:
	virtual void processForce(double t, SolidBox* box) {};
	virtual void processForce(double t, Particle* particle) {};
	virtual void update(double t) {};
};

