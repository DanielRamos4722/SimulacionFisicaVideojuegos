#pragma once

#include "ForceGenerator.h"

class GunForce : public ForceGenerator
{
public:
    GunForce(PxTransform* playerT, float farForce, float nearStiff, float damping, float radius) : playerT(playerT), farForce(farForce), nearStiff(nearStiff), damping(damping), radius(radius) {};
    void update(double t) override {};
    void processForce(double t, Particle* particle) override;
    inline float clamp(float x, float low, float high)
    {
        return (x < low) ? low : (x > high) ? high : x;
    }
    inline float smoothstep(float edge0, float edge1, float x)
    {
        x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
        return x * x * (3.0f - 2.0f * x);
    }

private:
    PxTransform* playerT;
    float farForce;
    float nearStiff;
    float damping;
    float radius;
};

