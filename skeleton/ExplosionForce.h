#pragma once

#include "ForceGenerator.h"

class ExplosionForce : public ForceGenerator
{
public:
    ExplosionForce(Vector3D center, float K, float radius, float decayTime) : center(center), K(K), radius(radius), decayTime(decayTime), aliveTime(0.0f), go(false) {};
    void update(double t) override;
    void processForce(double t, Particle* particle) override;

private:
    Vector3D center;
    float K;
    float aliveTime;
    float decayTime;
    float radius;
    bool go;
};

