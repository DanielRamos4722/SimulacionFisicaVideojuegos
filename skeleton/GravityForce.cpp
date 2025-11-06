#include "GravityForce.h"

void
GravityForce::processForce(double t, Particle* particle)
{
	Vector3D force = gravityForce * particle->getMass();
	particle->addForce(force);
}
