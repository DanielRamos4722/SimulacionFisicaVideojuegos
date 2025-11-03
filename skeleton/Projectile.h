#pragma once

#include "Particle.h"

#define gravityR -9.81f

class Projectile : public Particle
{
public:
	Projectile(Vector3D pos, Vector3D velR, Vector3D velS, float massR, float damp, Vector4 color = { 1.0f, 0.0f, 0.0f, 1.0f }, PxReal size = 2.0f);

private:
	Vector3D velS;
	Vector3D velR;
	float massS;
	float massR;
	float gravityS;
};

