#include "WindForce.h"

void
WindForce::processForce(double t, SolidBox* box)
{
    PxRigidDynamic* rigid = box->getRigid();
    Vector3D diff = windVel - rigid->getLinearVelocity();
    float finalVel = diff.magnitude();
    Vector3D force = k1 * diff + k2 * finalVel * diff;

    rigid->addForce(force);
}

void
WindForce::processForce(double t, Particle* particle)
{
    Vector3D diff = windVel - particle->getCurrentVel();
    float finalVel = diff.magnitude();
    Vector3D force = k1 * diff + k2 * finalVel * diff;

    particle->addForce(force);
}
