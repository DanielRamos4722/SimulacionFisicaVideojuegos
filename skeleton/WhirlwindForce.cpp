#include "WhirlwindForce.h"

void
WhirlwindForce::processForce(double t, SolidBox* box)
{
    PxRigidDynamic* rigid = box->getRigid();
    Vector3D pos = rigid->getGlobalPose().p;
    Vector3D diff = pos - center;

    float distance = diff.magnitude();
    if (distance < radius)
    {
        Vector3D tangent(-diff.getZ(), 0.0f, diff.getX());
        tangent.normalized();

        float falloff = 1.0f - (distance / radius);
        Vector3D windVel = tangent * K * falloff;

        Vector3D diffVel = windVel - rigid->getLinearVelocity();
        float finalVel = diffVel.magnitude();
        Vector3D force = k1 * diffVel + k2 * finalVel * diffVel;

        rigid->addForce(force);
    }
}

void
WhirlwindForce::processForce(double t, Particle* particle)
{
    Vector3D pos = particle->getCurrentPos();
    Vector3D diff = pos - center;

    float distance = diff.magnitude();
    if (distance < radius)
    {
        Vector3D tangent(-diff.getZ(), 0.0f, diff.getX());
        tangent.normalized();

        float falloff = 1.0f - (distance / radius);
        Vector3D windVel = tangent * K * falloff;

        Vector3D diffVel = windVel - particle->getCurrentVel();
        float finalVel = diffVel.magnitude();
        Vector3D force = k1 * diffVel + k2 * finalVel * diffVel;

        particle->addForce(force);
    }
}
