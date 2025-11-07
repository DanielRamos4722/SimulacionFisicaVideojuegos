#include "ExplosionForce.h"

void
ExplosionForce::processForce(double t, Particle* particle)
{
    if (go)
    {
        Vector3D diff = particle->getCurrentPos() - center;
        float distance = (particle->getCurrentPos() - center).magnitude();

        if (distance < radius)
        {
            Vector3D dir = diff.normalized();
            float strength = (K / (distance * distance)) * exp(-aliveTime / decayTime);
            Vector3D force = dir * strength;
            particle->addForce(force);
        }
    }
}

void
ExplosionForce::update(double t)
{
    aliveTime += t;
    if (aliveTime > 10.0f && !go)
    {
        go = true;
        aliveTime = 0.0f;
    }
}