#pragma once

#include "ForceGenerator.h"
#include "vector3D.h"

class WindForce : public ForceGenerator
{
public:
    WindForce(Vector3D windVel, Vector3D origin, float range, float k1, float k2 = 0.0f) : windVel(windVel), origin(origin), range(range), k1(k1), k2(k2) {};
    void processForce(double t, SolidBox* box) override;
    void processForce(double t, Particle* particle) override;

protected:
    Vector3D origin;
    float range;
    Vector3D windVel;
    float k1;
    float k2;
};