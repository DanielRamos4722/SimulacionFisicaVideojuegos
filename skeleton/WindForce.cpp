#include "WindForce.h"

void
WindForce::processForce(double t, Particle* particle)
{
    Vector3D diff = windVel - particle->getCurrentVel();
    float finalVel = diff.magnitude();
    Vector3D force = k1 * diff + k2 * finalVel * diff;

    particle->addForce(force);
}
