#pragma once

#include "Particle.h"

class ForceGenerator
{
public:
	virtual void processForce(double t, Particle* particle) {};
	virtual void update(double t) {};
};

