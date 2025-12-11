#include "GravityForce.h"

void
GravityForce::processForce(double t, SolidBox* box)
{
	PxRigidDynamic* rigid = box->getRigid();
	Vector3D force = gravityForce * rigid->getMass();
	rigid->addForce(force);
}

void
GravityForce::processForce(double t, Particle* particle)
{
	Vector3D force = gravityForce * particle->getMass();
	particle->addForce(force);
}
