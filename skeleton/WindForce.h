#pragma once

#include "ForceGenerator.h"

class WindForce : public ForceGenerator
{
public:
    WindForce(Vector3D windVel, float k1, float k2 = 0.0f) : windVel(windVel), k1(k1), k2(k2) {};
    void processForce(double t, Particle* particle) override;

protected:
    Vector3D windVel;
    float k1;
    float k2;
};