#include "SpringForce.h"

SpringForce::SpringForce(double k, double restingLength, const Vector3D& anchorPos) : k(k), restingLength(restingLength)
{
	other = new Particle(anchorPos, Vector3D(), 1.0f, 0.98f);
}

void
SpringForce::processForce(double t, Particle* particle)
{
	Vector3D relativePosVector = other->getCurrentPos() - particle->getCurrentPos();
	Vector3D force;

	const float length = relativePosVector.magnitude();
	const float deltaX = length - restingLength;

	force = relativePosVector * deltaX * k;

	particle->addForce(force);
}