#include "BuoyancyForce.h"

BuoyancyForce::BuoyancyForce(float h, float V, float d, float yPos) : height(h), volume(V), liquidDensity(d)
{
    liquidParticle = new Particle(Vector3(-180, yPos, 0), Vector3(0, 0, 0), 1.0f, 0.98f, Vector3(60.0f, 2.0f, 20.0f), Vector4(0.0f, 0.0f, 1.0f, 0.3f));
}

void
BuoyancyForce::processForce(double t, SolidBox* box)
{
    PxRigidDynamic* rigid = box->getRigid();
    if (abs(rigid->getGlobalPose().p.x - liquidParticle->getCurrentPos().getX()) < 60.0f && abs(rigid->getGlobalPose().p.z - liquidParticle->getCurrentPos().getZ()) < 20.0f)
    {
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
}

void
BuoyancyForce::processForce(double t, Particle* particle)
{
    if (abs(particle->getCurrentPos().getX() - liquidParticle->getCurrentPos().getX()) < 60.0f && abs(particle->getCurrentPos().getZ() - liquidParticle->getCurrentPos().getZ()) < 20.0f)
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
}
