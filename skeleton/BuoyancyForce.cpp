#include "BuoyancyForce.h"

BuoyancyForce::BuoyancyForce(float h, float V, float d) : height(h), volume(V), liquidDensity(d)
{
    liquidParticle = new Particle(Vector3(0, h, 0), Vector3(0, 0, 0), 1.0f, 0.98f, Vector3(100.0f, 10.0f, 100.0f), Vector4(0.0f, 0.0f, 1.0f, 0.0f));
}

void
BuoyancyForce::processForce(double t, SolidBox* box)
{
    PxRigidDynamic* rigid = box->getRigid();
    float h = rigid->getGlobalPose().p.y;
    float h0 = liquidParticle->getCurrentPos().getY();

    Vector3 f(0, 0, 0);
    float immersed = 0.0;
    if (h - h0 > height * 0.5) {
        immersed = 0.0;
    }
    else if (h0 - h > height * 0.5) {
        immersed = 1.0;
    }
    else {
        immersed = (h0 - h) / height + 0.5;
    }

    f.y = liquidDensity * volume * immersed * 9.8;

    rigid->addForce(f);
}

void
BuoyancyForce::processForce(double t, Particle* particle)
{
    float h = particle->getCurrentPos().getY();
    float h0 = liquidParticle->getCurrentPos().getY();

    Vector3 f(0, 0, 0);
    float immersed = 0.0;
    if (h - h0 > height * 0.5) {
        immersed = 0.0;
    }
    else if (h0 - h > height * 0.5) {
        immersed = 1.0;
    }
    else {
        immersed = (h0 - h) / height + 0.5;
    }

    f.y = liquidDensity * volume * immersed * 9.8;

    particle->addForce(f);
}
