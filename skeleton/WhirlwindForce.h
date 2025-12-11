#pragma once

#include "WindForce.h"

class WhirlwindForce : public WindForce
{
public:
    WhirlwindForce(float k1, float k2, Vector3D center, float K, float radius)
        : WindForce({}, k1, k2), center(center), K(K), radius(radius) {};
    void processForce(double t, SolidBox* box) override;
    void processForce(double t, Particle* particle) override;

private:
    Vector3D center;
    float K;
    float radius;
};

